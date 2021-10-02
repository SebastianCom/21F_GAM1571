
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Player.h"

namespace fw {
	Player::Player(fw::FWCore& fwCore) :m_FWCore(fwCore)
	{
		m_Speed = 5;
	}
	Player::~Player()
	{
	}
	void Player::OnUpdate(float deltaTime)
	{

		if (m_FWCore.IsKeyDown(VK_RIGHT))
		{
			m_X += m_Speed * deltaTime;
		}
		if (m_FWCore.IsKeyDown(VK_LEFT))
		{
			m_X -= m_Speed * deltaTime;
		}

		if (m_FWCore.IsKeyDown(VK_UP))
		{
			m_Y += m_Speed * deltaTime;
		}
		if (m_FWCore.IsKeyDown(VK_DOWN))
		{
			m_Y -= m_Speed * deltaTime;
		}

	}
	void Player::Draw()
	{
	}
} // namespace fw
