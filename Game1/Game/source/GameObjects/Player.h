#pragma once
#include "Framework.h"
#include "Objects/PlayerController.h"

namespace fw {

	class Player : public GameObject
	{
	public:

		Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos, PlayerController* playerController);
		~Player();

		void OnUpdate(float deltaTime)override;


	private:
		
		PlayerController* m_pPlayerController;
	};

} // namespace fw
