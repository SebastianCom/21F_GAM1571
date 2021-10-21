
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Enemy.h"

namespace fw {
	Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos) 
		: GameObject(pMesh, pShader, pos)
	{
		m_Speed = 5;
		SetPosition(pos);
		m_Radius = 0.80f;
	}
	Enemy::~Enemy()
	{
	}
	void Enemy::OnUpdate(float deltaTime)
	{


	}


} // namespace fw
