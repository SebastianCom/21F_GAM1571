#pragma once
#include "Framework.h"

namespace fw {

	class PickUp : public GameObject
	{
	public:

		PickUp(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos);
		~PickUp();

		void OnUpdate(float deltaTime)override;

		void Flash(float deltaTime);
	

	private:
		float m_FlashTimer;
		bool m_IncreaseTimer;
	};

} // namespace fw
