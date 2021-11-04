
#include "Framework.h"
#include "Objects/GameObject.h"
#include "Enemy.h"

namespace fw {
	Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos) 
		: GameObject(pMesh, pShader, pos)
	{
		m_Speed = 1;
		SetPosition(pos);
		m_Radius = 0.80f;
		m_BackUpSpot = {fw::RandomFloat(-14,14),fw::RandomFloat(-14,14)};
	}
	Enemy::~Enemy()
	{
	}
	void Enemy::OnUpdate(float deltaTime)
	{
		//If Enemies at i is ready to die set the scale value to the shrinkage timer.

			if (GetReadyToDie() == true)
			{
				SetScale(GetShrinkageTimer());
			}

	}

	void Enemy::MoveTo(float deltaTime, fw::vec2 position)
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

	void Enemy::SocailDistance(float deltaTime)
	{

		MoveTo(deltaTime, fw::vec2(m_BackUpSpot));
		
		if (CheckCollision(m_BackUpSpot,1.0f) == true) //Janky but i like it for now. There seems to be a que due to the way it used the vector. 
		{
			m_Chasing = true;
		}
		
	}




} // namespace fw
