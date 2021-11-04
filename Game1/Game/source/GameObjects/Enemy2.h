#pragma once
#include "Framework.h"

namespace fw {

	class Enemy2 : public GameObject
	{
	public:

		Enemy2(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos);
		~Enemy2();

		void OnUpdate(float deltaTime)override;

		void MoveTo(float deltaTime, fw::vec2 position) override;
	
	private:
		
	};

} // namespace fw
