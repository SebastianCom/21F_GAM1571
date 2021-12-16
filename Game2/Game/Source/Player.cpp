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
    KeyPressed = false;
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{  


    MoveTheBox();
    MoveTheFucker(deltaTime);

    float x = float(round(m_Position.x / m_pTileMap->GetTileSize().x));
    float y = float(round(m_Position.y / m_pTileMap->GetTileSize().x));

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

void Player::MoveTheBox()
{
    if (m_pPlayerController->IsPushHeld() && !KeyPressed)
    {
        PushBlocks(int(round(m_Position.x / m_pTileMap->GetTileSize().x)), int(round(m_Position.y / m_pTileMap->GetTileSize().x)));
        KeyPressed = true;
    }
    else if (m_pPlayerController->IsPullHeld() && !KeyPressed)
    {
        PullBlocks(int(round(m_Position.x / m_pTileMap->GetTileSize().x)), int(round(m_Position.y / m_pTileMap->GetTileSize().x)));
        KeyPressed = true;
    }
    else if (!m_pPlayerController->IsPushHeld() && !m_pPlayerController->IsPullHeld())
    {
        KeyPressed = false;
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


// JIMMY: i know these next 2 methods have a lot a repated code... i have tried to figure out a way to make them a function instead of repeating but there are
// a good amount of minute chnages between each direction case. Maybe that is something we can go over next semester
// i may not have been able to lower the repeated code however there should be no hard coded values other than 0 and 1 so thats something;

void Player::PullBlocks(int x, int y)
{
    for (int i = 0; i < NumDirections; i++) //up,down,left,right in that order
    {
        if (i == Up)
        {
            for (int i = y; i < m_pTileMap->GetTileMapHeight(); i++)
            {
                char tile = m_pTileMap->GetTile((i * m_pTileMap->GetTileMapWidth()) + x);
                if (m_pTileMap->GetTileProperties(tile).Moveable == true)
                {
                    if (i - 1 != y)
                    {
                        char CurrentTile = i * m_pTileMap->GetTileMapWidth() + x;
                        char NextTile = (i - 1) * m_pTileMap->GetTileMapWidth() + x;
                        m_pTileMap->SwapTiles(CurrentTile, NextTile);
                    }
                    break;
                }
            }
        }
        if (i == Down)
        {
            for (int i = y; i > 0; i--)
            {
                char tile = m_pTileMap->GetTile((i * m_pTileMap->GetTileMapWidth()) + x);
                if (m_pTileMap->GetTileProperties(tile).Moveable == true)
                {
                    if (i + 1 != y)
                    {
                        char CurrentTile = i * m_pTileMap->GetTileMapWidth() + x;
                        char NextTile = (i + 1) * m_pTileMap->GetTileMapWidth() + x;
                        m_pTileMap->SwapTiles(CurrentTile, NextTile);

                    }
                    break;
                }
            }
        }
        if (i == Left)
        {
            for (int i = x; i > 0; i--)
            {
                char tile = m_pTileMap->GetTile((y * m_pTileMap->GetTileMapWidth()) + i);
                if (m_pTileMap->GetTileProperties(tile).Moveable == true)
                {
                    if (i + 1 != x)
                    {
                        char CurrentTile = y * m_pTileMap->GetTileMapWidth() + i;
                        char NextTile = y * m_pTileMap->GetTileMapWidth() + (i + 1);
                        m_pTileMap->SwapTiles(CurrentTile, NextTile);
                    }
                    break;
                }
            }
        }
        if (i == Right)
        {
            for (int i = x; i < m_pTileMap->GetTileMapWidth(); i++)
            {
                char tile = m_pTileMap->GetTile((y * m_pTileMap->GetTileMapWidth()) + i);
                if (m_pTileMap->GetTileProperties(tile).Moveable == true)
                {
                    if (i - 1 != x)
                    {
                        char CurrentTile = y * m_pTileMap->GetTileMapWidth() + i;
                        char NextTile = y * m_pTileMap->GetTileMapWidth() + (i - 1);
                        m_pTileMap->SwapTiles(CurrentTile, NextTile);
                    }
                    break;
                }
            }
        }
    }
}

void Player::PushBlocks(int x, int y)
{
    for (int i = 0; i < NumDirections; i++) //up,down,left,right in that order
    {
        if (i == Up)
        {
            for (int i = y; i < m_pTileMap->GetTileMapHeight(); i++)
            {
                char tile = m_pTileMap->GetTile((i * m_pTileMap->GetTileMapWidth()) + x);
                if (m_pTileMap->GetTileProperties(tile).Moveable == true)
                {
                    char tile2 = m_pTileMap->GetTile(( (i+1) * m_pTileMap->GetTileMapWidth()) + x);
                    if (m_pTileMap->GetTileProperties(tile2).Walkable)
                    {
                        char CurrentTile = i * m_pTileMap->GetTileMapWidth() + x;
                        char NextTile = (i + 1) * m_pTileMap->GetTileMapWidth() + x;
                        m_pTileMap->SwapTiles(CurrentTile, NextTile);
                    }
                    break;
                }
            }
        }
        if (i == Down)
        {
            for (int i = y; i > 0; i--)
            {
                char tile = m_pTileMap->GetTile((i * m_pTileMap->GetTileMapWidth()) + x);
                if (m_pTileMap->GetTileProperties(tile).Moveable == true)
                {
                    char tile2 = m_pTileMap->GetTile(((i - 1) * m_pTileMap->GetTileMapWidth()) + x);
                    if (m_pTileMap->GetTileProperties(tile2).Walkable)
                    {
                        char CurrentTile = i * m_pTileMap->GetTileMapWidth() + x;
                        char NextTile = (i - 1) * m_pTileMap->GetTileMapWidth() + x;
                        m_pTileMap->SwapTiles(CurrentTile, NextTile);

                    }
                    break;
                }
            }
        }
        if (i == Left)
        {
            for (int i = x; i > 0; i--)
            {
                char tile = m_pTileMap->GetTile((y * m_pTileMap->GetTileMapWidth()) + i);
                if (m_pTileMap->GetTileProperties(tile).Moveable == true)
                {
                    char tile2 = m_pTileMap->GetTile(( y * m_pTileMap->GetTileMapWidth()) + (i-1));
                    if (m_pTileMap->GetTileProperties(tile2).Walkable)
                    {
                        char CurrentTile = y * m_pTileMap->GetTileMapWidth() + i;
                        char NextTile = y * m_pTileMap->GetTileMapWidth() + (i - 1);
                        m_pTileMap->SwapTiles(CurrentTile, NextTile);
                    }
                    break;
                }
            }
        }
        if (i == Right)
        {
            for (int i = x; i < m_pTileMap->GetTileMapWidth(); i++)
            {
                char tile = m_pTileMap->GetTile((y * m_pTileMap->GetTileMapWidth()) + i);
                if (m_pTileMap->GetTileProperties(tile).Moveable == true)
                {
                    char tile2 = m_pTileMap->GetTile((y * m_pTileMap->GetTileMapWidth()) + (i + 1));
                    if (m_pTileMap->GetTileProperties(tile2).Walkable)
                    {
                        char CurrentTile = y * m_pTileMap->GetTileMapWidth() + i;
                        char NextTile = y * m_pTileMap->GetTileMapWidth() + (i + 1);
                        m_pTileMap->SwapTiles(CurrentTile, NextTile);
                    }
                    break;
                }
            }
        }
    }
}
