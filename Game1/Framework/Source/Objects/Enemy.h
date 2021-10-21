#pragma once
#include "Framework.h"

namespace fw {

	class Enemy : public GameObject
	{
	public:

		Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos);
		~Enemy();

		void OnUpdate(float deltaTime)override;
	
	private:
		
	};

} // namespace fw
