
#include "Framework.h"
#include "Objects/GameObject.h"
#include "Bullet.h"

namespace fw {
	Bullet::Bullet(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos, PlayerController* bulletController)
		: GameObject(pMesh, pShader, pos),
		m_pBulletController(bulletController)

	{
		Init(pos);
	}
	Bullet::~Bullet()
	{
	}
	void Bullet::OnUpdate(float deltaTime)
	{
		if (m_IsActive)
		{
			if (m_pBulletController->ShootingUp())
			{
				m_IsShooting = true;
				m_ShootingUp = true;
				m_IsActive = false;
			}
			if (m_pBulletController->ShootingDown())
			{
				m_IsShooting = true;
				m_ShootingDown = true;
				m_IsActive = false;
			}
			if (m_pBulletController->ShootingLeft())
			{
				m_IsShooting = true;
				m_ShootingLeft = true;
				m_IsActive = false;
			}
			if (m_pBulletController->ShootingRight())
			{
				m_IsShooting = true;
				m_ShootingRight = true;
				m_IsActive = false;
			}

		}

		if (m_ShootingUp)
		{
			m_Position.y += m_Speed * deltaTime;
		}
		if (m_ShootingLeft)
		{
			m_Position.x -= m_Speed * deltaTime;
		}
		if (m_ShootingDown)
		{
			m_Position.y -= m_Speed * deltaTime;
		}
		if (m_ShootingRight)
		{
			m_Position.x += m_Speed * deltaTime;
		}
		
		//If the player hits two opposite directions the bullet will stay in place fighting itself, This way when both are hit at the same time the bullet still moves in a right direction
		if (m_ShootingUp && m_ShootingDown)
		{
			m_Position.y += m_Speed * deltaTime;
		}
		if (m_ShootingLeft && m_ShootingRight)
		{
			m_Position.x += m_Speed * deltaTime;
		}

		
	}


	void Bullet::Init(fw::vec2 pos)
	{
		m_Speed = 5;
		SetPosition(pos);
		m_Radius = 0.20f;
		m_IsShooting = false;
		m_ReadyToDie = false;
		m_ShootingUp = false;
		m_ShootingLeft = false;
		m_ShootingDown = false;
		m_ShootingRight = false;
		m_Shrinkage = 0.0f;
		m_IsActive = true;
	}

	void Bullet::SetIsShooting(bool shooting)
	{
		m_IsShooting = shooting;
	}

	bool Bullet::GetIsShooting()
	{
		return m_IsShooting;
	}



} // namespace fw
