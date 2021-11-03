#pragma once
#include "Framework.h"

namespace fw {

	class Enemy : public GameObject
	{
	public:

		Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos);
		~Enemy();

		void OnUpdate(float deltaTime)override;

		void MoveTo(float deltaTime, fw::vec2 position) override;
		void SocailDistance(float deltaTime) override;
	
	private:
		
		fw::vec2 m_BackUpSpot;
	};

} // namespace fw
