#include "Framework.h"
#include "Player.h"
#include "PlayerController.h"
#include "TileMap.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController, TileMap* pMap)
    : GameObject( pMesh, pShader, pTexture, pos, 1)
    , m_pPlayerController( pController )
    , m_pTileMap(pMap)
{
    m_PlayerScale = fw::vec2(5, 5);
    m_Speed = 50.0f;
    m_CurrentSprite = m_Sprites["Player Down"];
    m_AnimTimer = 1.0f;
    m_Position = pos;
    m_PlayerDirection = Down;
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{  

    if (m_pPlayerController->IsPushHeld())
    {
        PushBlocks(round(m_Position.x / m_pTileMap->GetTileSize().x), round(m_Position.y / m_pTileMap->GetTileSize().x));
    }
    else if (m_pPlayerController->IsPullHeld())
    {
        PullBlocks(round(m_Position.x / m_pTileMap->GetTileSize().x), round(m_Position.y / m_pTileMap->GetTileSize().x));
    }

    MoveTheFucker(deltaTime);

    float x = round(m_Position.x / m_pTileMap->GetTileSize().x);
    float y = round(m_Position.y / m_pTileMap->GetTileSize().x);

    ImGui::SliderFloat( "X", &x, 0, 10 );
    ImGui::SliderFloat( "Y", &y, 0, 10 );
}

void Player::Draw(fw::vec2 camPos, fw::vec2 projScale)
{
    int sheetWidth = m_pSpriteSheet->GetSheetWidth();
    fw::vec2 uvOffset = m_pSpriteSheet->GetSpriteInfo(m_CurrentSprite).UVOffset;
    fw::vec2 uvScale = m_pSpriteSheet->GetSpriteInfo(m_CurrentSprite).UVScale;
   
    m_pMesh->Draw(m_pShader, m_pTexture, m_PlayerScale, m_Position, 0.0f, camPos, projScale, uvScale, uvOffset);
}


//------------------------------ My Functions ------------------------------------------------------

void Player::MoveTheFucker(float deltaTime)
{
  
    if (m_pPlayerController->IsRightHeld())
    {
        m_Position.x += m_Speed * deltaTime;
        m_AnimTimer -= deltaTime;
        m_PlayerDirection = Right;

        if (!m_pPlayerController->IsUpHeld() && !m_pPlayerController->IsDownHeld()) //fixes animation tears
        {
            if (m_AnimTimer >= 0.8f)
            {
                m_CurrentSprite = m_Sprites["Player Right"];
            }
            if (m_AnimTimer >= 0.6f && m_AnimTimer < 0.8f)
            {
                m_CurrentSprite = m_Sprites["Player Right2"];
            }
            if (m_AnimTimer >= 0.3f && m_AnimTimer < 0.6f)
            {
                m_CurrentSprite = m_Sprites["Player Right"];
            }
            if (m_AnimTimer >= 0.0f && m_AnimTimer < 0.3f)
            {
                m_CurrentSprite = m_Sprites["Player Right3"];
            }
        }

    }

    if (m_pPlayerController->IsLeftHeld())
    {
        m_Position.x -= m_Speed * deltaTime;
        m_AnimTimer -= deltaTime;
        m_PlayerDirection = Left;

        if (!m_pPlayerController->IsUpHeld() && !m_pPlayerController->IsDownHeld()) //fixes animation tears
        {
            if (m_AnimTimer >= 0.8f)
            {
                m_CurrentSprite = m_Sprites["Player Left"];
            }
            if (m_AnimTimer >= 0.6f && m_AnimTimer < 0.8f)
            {
                m_CurrentSprite = m_Sprites["Player Left2"];
            }
            if (m_AnimTimer >= 0.3f && m_AnimTimer < 0.6f)
            {
                m_CurrentSprite = m_Sprites["Player Left"];
            }
            if (m_AnimTimer >= 0.0f && m_AnimTimer < 0.3f)
            {
                m_CurrentSprite = m_Sprites["Player Left3"];
            }
        }
    }

    if (m_pPlayerController->IsUpHeld())
    {
        m_Position.y += m_Speed * deltaTime;
        m_AnimTimer -= deltaTime;
        m_PlayerDirection = Up;

        if (m_AnimTimer >= 0.8f)
        {
            m_CurrentSprite = m_Sprites["Player Up"];
        }
        if (m_AnimTimer >= 0.6f && m_AnimTimer < 0.8f)
        {
            m_CurrentSprite = m_Sprites["Player Up2"];
        }
        if (m_AnimTimer >= 0.3f && m_AnimTimer < 0.6f)
        {
            m_CurrentSprite = m_Sprites["Player Up"];
        }
        if (m_AnimTimer >= 0.0f && m_AnimTimer < 0.3f)
        {
            m_CurrentSprite = m_Sprites["Player Up3"];
        }
    }

    if (m_pPlayerController->IsDownHeld())
    {
        m_Position.y-= m_Speed * deltaTime;
        m_AnimTimer -= deltaTime;
        m_PlayerDirection = Down;

        if (m_AnimTimer >= 0.8f)
        {
            m_CurrentSprite = m_Sprites["Player Down"];
        }
        if (m_AnimTimer >= 0.6f && m_AnimTimer < 0.8f)
        {
            m_CurrentSprite = m_Sprites["Player Down2"];
        }
        if (m_AnimTimer >= 0.3f && m_AnimTimer < 0.6f)
        {
            m_CurrentSprite = m_Sprites["Player Down"];
        }
        if (m_AnimTimer >= 0.0f && m_AnimTimer < 0.3f)
        {
            m_CurrentSprite = m_Sprites["Player Down3"];
        }
    }

    if (m_AnimTimer <= 0.0f)
    {
        m_AnimTimer = 1.0f;
    }
}

fw::vec2 Player::GetPosition()
{
    return m_Position;
}

void Player::SetPosition(fw::vec2 pos)
{
    m_Position = pos;
}

void Player::PullBlocks(int x, int y)
{

}

void Player::PushBlocks(int x, int y)
{
    for (int i = 0; i < NumDirections; i++) //up,down,left,right in that order
    {
        if (i == Up)
        {
            for (int i = y; y < m_pTileMap->GetTileMapHeight(); i ++)
            {
               char tile = m_pTileMap->GetTile((i * m_pTileMap->GetTileMapWidth()) + x);
                if (m_pTileMap->GetTileProperties(tile).Moveable == true)
                {
                    int bp = 1;
                }
            }
        }
        if (i == Down)
        {

        }
        if (i == Left)
        {

        }
        if (i == Right)
        {

        }
    }
}
