
#include "Framework.h"
#include "Objects/GameObject.h"
#include "Enemy2.h"

namespace fw {
	Enemy2::Enemy2(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos) 
		: GameObject(pMesh, pShader, pos)
	{
		m_PatrolSpotAlpha = fw::vec2(0, 0);
		m_PatrolSpotBeta = fw::vec2(0, 0);
		m_Speed = 1.0f;
		SetPosition(pos);
		m_Radius = 0.80f;
		int tickCount = 0;
		while (m_PatrolSpotAlpha == m_PatrolSpotBeta && m_PatrolSpotAlpha.DistanceTo(m_PatrolSpotBeta) < 5 || tickCount == 100)
		{
			m_PatrolSpotAlpha = { fw::RandomFloat(-14,14),fw::RandomFloat(-14,14) };
			m_PatrolSpotBeta = { fw::RandomFloat(-14,14),fw::RandomFloat(-14,14) };
			tickCount++;
		}
	}
	Enemy2::~Enemy2()
	{
	}
	void Enemy2::OnUpdate(float deltaTime)
	{
		//If Enemies at i is ready to die set the scale value to the shrinkage timer.

			if (GetReadyToDie() == true)
			{
				SetScale(GetShrinkageTimer());
			}

	}

	void Enemy2::MoveTo(float deltaTime, fw::vec2 position)
	{
		if (m_Position.x > position.x)
		{
			m_Position.x -= m_Speed * deltaTime;
		}
		if (m_Position.x < position.x)
		{
			m_Position.x += m_Speed * deltaTime;
		}
		if (m_Position.y > position.y)
		{
			m_Position.y -= m_Speed * deltaTime;
		}
		if (m_Position.y < position.y)
		{
			m_Position.y += m_Speed * deltaTime;
		}
	}





} // namespace fw
