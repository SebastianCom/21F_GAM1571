#include "Framework.h"
#include "Player.h"
#include "PlayerController.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController)
    : GameObject( pMesh, pShader, pTexture, pos )
    , m_pPlayerController( pController )
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 2.0f;
    if( m_pPlayerController->IsRightHeld() )
    {
        m_Position.x += speed * deltaTime;
    }

    ImGui::DragFloat( "X", &m_Position.x, 0.1f, -50, 50 );
    ImGui::DragFloat( "Y", &m_Position.y, 0.1f, -50, 50 );
}
