#include "Framework.h"
#include "Enemy.h"
#include "TileMap.h"
#include "PathFinder.h"


Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, TileMap* pMap)
    : GameObject( pMesh, pShader, pTexture, pos, 2)
{
    m_EnemyScale = fw::vec2(5, 5);
    m_Speed = 50.0f;
    m_Sprite = m_Sprites["Enemy Blue"];
    m_Position = pos;
    pTileMap = pMap;

    EnemyPathFinder = new PathFinder(pTileMap);
   
    NextTileIndex = 0;
    
    EndGoal = fw::vec2(8, 8);
    PathFound = false;
    StartPathFind();
   
    m_CurrentAIState = (AIStateFunction)&Enemy::AIState_Idle;

}

Enemy::~Enemy()
{
    delete EnemyPathFinder;
}

void Enemy::Update(float deltaTime)
{  
    (this->*m_CurrentAIState)(deltaTime);
   
    if (PathFound)
    {
        int index = EnemyPathFinder->GetPath(int(EndGoal.x), int(EndGoal.y));
        if (IsAtLocation(index) == false)
            MoveTo(index, deltaTime);
        else
            StartPathFind();
    }
}

void Enemy::Draw(fw::vec2 camPos, fw::vec2 projScale)
{
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

    //if (m_Position == newPosition)
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
    PathFound = EnemyPathFinder->FindPath((m_Position / pTileMap->GetTileSize()), int(EndGoal.x), int(EndGoal.y));
}

void Enemy::AIState_Idle(float deltaTime)
{

}

void Enemy::AIState_Searching(float deltaTime)
{
}

void Enemy::AIState_Chasing(float deltaTime)
{
}
