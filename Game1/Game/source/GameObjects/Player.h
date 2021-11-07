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

		bool IsShooting();

		void SetLives(int lives) { m_Lives = lives; }
		void DecrementLives() { m_Lives--; }
		int	 GetLives() { return m_Lives; }

		void SetScore(int Score) { m_Score = Score; }
		void IncrementScore() { m_Score += 10; }
		int	 GetScore() { return m_Score; }



	private:

		PlayerController* m_pPlayerController;
		int m_Lives;
		int m_Score;
	};

} // namespace fw
