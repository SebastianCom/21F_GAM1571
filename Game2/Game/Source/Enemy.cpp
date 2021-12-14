#include "Framework.h"
#include "Enemy.h"


Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos)
    : GameObject( pMesh, pShader, pTexture, pos, 2)
 
{
    m_EnemyScale = fw::vec2(5, 5);
    m_Speed = 50.0f;
    m_Sprite = m_Sprites["Enemy Blue"];
    m_Position = pos;

}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{  

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
