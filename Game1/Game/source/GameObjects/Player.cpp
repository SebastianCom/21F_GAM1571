
#include "Framework.h"
#include "Objects/GameObject.h"
#include "Player.h"

namespace fw {
	Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos, PlayerController* playerController) 
		:GameObject(pMesh, pShader, pos), 
		m_pPlayerController(playerController)
	{
		m_Speed = 10;
		SetPosition(pos);
		m_Radius = 0.80f;
		m_Lives = 3;
		m_Score = 0;
		
	}
	Player::~Player()
	{
	}
	void Player::OnUpdate(float deltaTime)
	{
		if (m_Position.x < 14.2f && m_Position.x > -14.2f
			&& m_Position.y < 14.2f && m_Position.y > -14.2f)
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
		else
		{
			if (m_Position.x >= 14.2f)
			{
				m_Position.x = 14.1f;
			}
			if (m_Position.x <= -14.2f)
			{
				m_Position.x = -14.1f;
			}
			if (m_Position.y >= 14.2f)
			{
				m_Position.y = 14.1f;
			}
			if (m_Position.y <= -14.2f)
			{
				m_Position.y = -14.1f;
			}
		}

	}
	bool Player::IsShooting()
	{
		if (m_pPlayerController->ShootingUp() == true
			|| m_pPlayerController->ShootingDown() == true
			|| m_pPlayerController->ShootingLeft() == true
			|| m_pPlayerController->ShootingRight() == true)
		{
			return true;
		}
		else return false;
	}
} // namespace fw
