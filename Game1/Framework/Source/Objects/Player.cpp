
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Player.h"

namespace fw {
	Player::Player(PlayerController* playerController)
	{
		m_Speed = 10;
		SetX(0);
		SetY(0);
		m_Radius = 0.80f;
		m_pPlayerController = playerController;
	}
	Player::~Player()
	{
	}
	void Player::OnUpdate(float deltaTime)
	{

		if (m_pPlayerController->IsRight())
		{
			m_X += m_Speed * deltaTime;
		}

		if (m_pPlayerController->IsLeft())
		{
			m_X -= m_Speed * deltaTime;
		}

		if (m_pPlayerController->IsUp())
		{
			m_Y += m_Speed * deltaTime;
		}
		if (m_pPlayerController->IsDown())
		{
			m_Y -= m_Speed * deltaTime;
		}

	}
	void Player::Draw()
	{
	}
} // namespace fw
