#include "Framework.h"
#include "Enemy.h"
#include "TileMap.h"
#include "PathFinder.h"
#include "Player.h"


std::random_device seed;
std::mt19937 mersenneTwister(seed());

float RandomFloat(float min, float max) //our good old friend the goal randomization method
{
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(mersenneTwister);
}


Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, TileMap* pMap, Player* pPlayer, int type)
    : GameObject( pMesh, pShader, pTexture, pos, 2)
{
    CurrentStateName = "null";
    m_EnemyDirection = Down;
    m_EnemyScale = fw::vec2(5, 5);
    m_Speed = 50.0f;
    if(type == 0)
        m_Sprite = m_Sprites["Enemy Blue"];
    if (type == 1)
        m_Sprite = m_Sprites["Enemy Orange"]; //json file said red, maybe i am slightly color blind but thats orange!
    m_Position = pos;
    pTileMap = pMap;
    m_pPlayer = pPlayer;

    EnemyPathFinder = new PathFinder(pTileMap);
   
    NextTileIndex = 0;
    
   
    PathFound = false;
   
    m_CurrentAIState = (AIStateFunction)&Enemy::AIState_Idle;
    IdleTimer = 1;
    Atlocation = false;

}

Enemy::~Enemy()
{
    delete EnemyPathFinder;
}

void Enemy::Update(float deltaTime)
{  
    (this->*m_CurrentAIState)(deltaTime);
   
}

void Enemy::Draw(fw::vec2 camPos, fw::vec2 projScale)
{
    ImGui::Text(CurrentStateName);
    fw::vec2 uvOffset = m_pSpriteSheet->GetSpriteInfo(m_Sprite).UVOffset;
    fw::vec2 uvScale = m_pSpriteSheet->GetSpriteInfo(m_Sprite).UVScale;
    m_pMesh->Draw(m_pShader, m_pTexture, m_EnemyScale, m_Position, 0.0f, camPos, projScale, uvScale, uvOffset);
}


//------------------------------ My Functions ------------------------------------------------------
//I do this because it helps me if i seperate functions i made from the draw and update functions.
//I get that for some i made the draw function but i still lie to divide my functions like this.

fw::vec2 Enemy::GetPosition()
{
    return m_Position;
}

void Enemy::SetPosition(fw::vec2 pos)
{
    m_Position = pos;
}

void Enemy::MoveTo(int index, float deltaTime)
{
    float x =  index % pTileMap->GetTileMapWidth() * (pTileMap->GetTileSize().x);
    float y =  index / pTileMap->GetTileMapWidth() * (pTileMap->GetTileSize().y);
    fw::vec2 newPosition = fw::vec2(x, y);
    if(m_Position.x < newPosition.x)
        m_Position.x += m_Speed * deltaTime;
    else if (m_Position.x > newPosition.x)
        m_Position.x -= m_Speed * deltaTime;
    else if (m_Position.y < newPosition.y)
        m_Position.y += m_Speed * deltaTime;
    else if (m_Position.y > newPosition.y)
        m_Position.y -= m_Speed * deltaTime;
}

bool Enemy::IsAtLocation(int index)
{
    float x2 = index % pTileMap->GetTileMapWidth() * (pTileMap->GetTileSize().x);
    float y2 = index / pTileMap->GetTileMapWidth() * (pTileMap->GetTileSize().y);
    fw::vec2 newPosition = fw::vec2(x2, y2);

    float x1 = m_Position.x;
    float y1 = m_Position.y;

    double distance = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)) );

    if (distance <= .5f)
    {
        m_Position = newPosition;
        return true;
    }
    else
        return false;
}



void Enemy::StartPathFind()
{
    PathFound = EnemyPathFinder->FindPath((m_Position / pTileMap->GetTileSize()), EndGoal.x, EndGoal.y);
}

void Enemy::AIState_Idle(float deltaTime)
{  
    DisplayState("Idle");
    if (IdleTimer > 0)
    {
        IdleTimer -= deltaTime;
    }
    else if (!Atlocation)
    {
        m_CurrentAIState = (AIStateFunction)&Enemy::AIState_Searching;
        IdleTimer = 1;
    }
    else if (Atlocation)
    {
        Atlocation = false;
        m_CurrentAIState = (AIStateFunction)&Enemy::AIState_Chasing;
        IdleTimer = 1;
    }
}

void Enemy::AIState_Searching(float deltaTime)
{
    DisplayState("Searching");
    if (PathFound && Atlocation == false)
    {
        int index = EnemyPathFinder->GetPath(int(EndGoal.x), int(EndGoal.y));
        if (IsAtLocation(index) == false)
        {
            MoveTo(index, deltaTime);
            if (IsAtLocation(EndGoal.y * pTileMap->GetTileMapWidth() + EndGoal.x))
                Atlocation = true;
            else
                Atlocation = false;
        }
        else
            StartPathFind();
    }
    else if (!PathFound)
    {
        RandomizeEndGoal();
        StartPathFind();
    }
    if (Atlocation)
    {
        m_CurrentAIState = (AIStateFunction)&Enemy::AIState_Idle;
        PathFound = false;
    }
}

void Enemy::AIState_Chasing(float deltaTime)
{
    DisplayState("Chasing");
    if (PathFound && Atlocation == false)
    {
        int index = EnemyPathFinder->GetPath(EndGoal.x, EndGoal.y);
        if (IsAtLocation(index) == false)
        {
            MoveTo(index, deltaTime);
            if (IsAtLocation(EndGoal.y * pTileMap->GetTileMapWidth() + EndGoal.x))
                Atlocation = true;
            else
                Atlocation = false;
        }
        else
            StartPathFind();
    }
    else if (!PathFound)
    {
        int x = m_pPlayer->GetPosition().x / pTileMap->GetTileSize().x;
        int y = m_pPlayer->GetPosition().y / pTileMap->GetTileSize().x;
        fw::vec2 Playerpos = fw::vec2(x, y);
        EndGoal = Playerpos;
        StartPathFind();
        if (!PathFound)
        {
            m_CurrentAIState = (AIStateFunction)&Enemy::AIState_Idle;
            PathFound = false;
            Atlocation = false;
        }
    }
    if (Atlocation)
    {
        m_CurrentAIState = (AIStateFunction)&Enemy::AIState_Idle;
        PathFound = false;
        Atlocation = false;
    }
}

void Enemy::RandomizeEndGoal()
{
    EndGoal.x = int(RandomFloat(1.0f, 9.0f));
    EndGoal.y = int(RandomFloat(1.0f, 9.0f));
}

void Enemy::ResetState()
{
    m_CurrentAIState = (AIStateFunction)&Enemy::AIState_Idle;
    PathFound = false;
    Atlocation = false;
    IdleTimer = 1;
    NextTileIndex = 0;
    EndGoal = fw::vec2(0, 0);
}

void Enemy::DisplayState(const char* state)
{
    CurrentStateName = state;
}

