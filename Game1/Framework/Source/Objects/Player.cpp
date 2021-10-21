
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Player.h"

namespace fw {
	Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos, PlayerController* playerController) 
		:GameObject(pMesh, pShader, pos), 
		m_pPlayerController(playerController)
	{
		m_Speed = 10;
		SetPosition(pos);
		m_Radius = 0.80f;
	}
	Player::~Player()
	{
	}
	void Player::OnUpdate(float deltaTime)
	{

		if (m_pPlayerController->IsRight())
		{
			m_Position.x += m_Speed * deltaTime;
		}

		if (m_pPlayerController->IsLeft())
		{
			m_Position.x -= m_Speed * deltaTime;
		}

		if (m_pPlayerController->IsUp())
		{
			m_Position.y += m_Speed * deltaTime;
		}
		if (m_pPlayerController->IsDown())
		{
			m_Position.y -= m_Speed * deltaTime;
		}

	}
} // namespace fw
