#include "Framework.h"
#include "Player.h"
#include "PlayerController.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController)
    : GameObject( pMesh, pShader, pTexture, pos)
    , m_pPlayerController( pController )
{
    m_PlayerScale = fw::vec2(5, 5);
    m_Speed = 50.0f;
    m_CurrentSprite = m_Sprites["Player Down"];
    m_AnimTimer = 1.0f;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{  



    MoveTheFucker(deltaTime);

    ImGui::SliderFloat( "X", &m_Position.x, 0, 450 );
    ImGui::SliderFloat( "Y", &m_Position.y, 0, 450 );
}

void Player::Draw(fw::vec2 camPos, fw::vec2 projScale)
{
    float sheetWidth = m_pSpriteSheet->GetSheetWidth();
    fw::vec2 uvOffset = m_pSpriteSheet->GetSpriteInfo(m_CurrentSprite).UVOffset;
    fw::vec2 uvScale = m_pSpriteSheet->GetSpriteInfo(m_CurrentSprite).UVScale;
   
    m_pMesh->Draw(m_pShader, m_pTexture, m_PlayerScale, m_Position, 0.0f, camPos, projScale, sheetWidth, uvScale, uvOffset);
}

void Player::MoveTheFucker(float deltaTime)
{
  
    if (m_pPlayerController->IsRightHeld())
    {
        m_Position.x += m_Speed * deltaTime;
        m_AnimTimer -= deltaTime;

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

    if (m_pPlayerController->IsLeftHeld())
    {
        m_Position.x -= m_Speed * deltaTime;
        m_AnimTimer -= deltaTime;

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

    if (m_pPlayerController->IsUpHeld())
    {
        m_Position.y += m_Speed * deltaTime;
        m_AnimTimer -= deltaTime;

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
