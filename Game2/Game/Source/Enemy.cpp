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
}

Enemy::~Enemy()
{
    delete EnemyPathFinder;
}

void Enemy::Update(float deltaTime)
{  
   
    if (PathFound)
    {
        int temp = EnemyPathFinder->GetPath(EndGoal.x, EndGoal.y);
        if (IsAtLocation(temp) == false)
            MoveTo(temp);
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

void Enemy::MoveTo(int index)
{
    float x =  index % pTileMap->GetTileMapWidth() * (pTileMap->GetTileSize().x);
    float y =  index / pTileMap->GetTileMapWidth() * (pTileMap->GetTileSize().y);
    fw::vec2 newPosition = fw::vec2(x, y);
    if(m_Position.x < newPosition.x)
        m_Position.x += 50;
    else if (m_Position.x > newPosition.x)
        m_Position.x -= 50;
    else if (m_Position.y < newPosition.y)
        m_Position.y += 50;
    else if (m_Position.y > newPosition.y)
        m_Position.y -= 50;
}

bool Enemy::IsAtLocation(int index)
{
    float x = index % pTileMap->GetTileMapWidth() * (pTileMap->GetTileSize().x);
    float y = index / pTileMap->GetTileMapWidth() * (pTileMap->GetTileSize().y);
    fw::vec2 newPosition = fw::vec2(x, y);

    if (m_Position == newPosition)
    {
        return true;
    }
    else
        return false;
}

void Enemy::StartPathFind()
{
    PathFound = EnemyPathFinder->FindPath((m_Position / pTileMap->GetTileSize()), EndGoal.x, EndGoal.y);
}
