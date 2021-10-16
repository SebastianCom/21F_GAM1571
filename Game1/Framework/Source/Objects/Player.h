#pragma once
#include "Framework.h"
#include "PlayerController.h"

namespace fw {

	class Player : public GameObject
	{
	public:

		Player(PlayerController* playerController);
		~Player();

		void OnUpdate(float deltaTime)override;
		void Draw()override;


	private:
		
		PlayerController* m_pPlayerController;
	};

} // namespace fw
