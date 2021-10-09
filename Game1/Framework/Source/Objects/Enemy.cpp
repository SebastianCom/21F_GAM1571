
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Enemy.h"

namespace fw {
	Enemy::Enemy(float X, float Y) 
	{
		m_Speed = 5;
		SetX(X);
		SetY(Y);
		m_Radius = 0.80f;
	}
	Enemy::~Enemy()
	{
	}
	void Enemy::OnUpdate(float deltaTime)
	{


	}
	void Enemy::Draw()
	{
	}

} // namespace fw
