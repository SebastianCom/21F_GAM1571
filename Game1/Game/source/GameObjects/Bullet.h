#pragma once
#include "Framework.h"

namespace fw {

	class Bullet : public GameObject
	{
	public:

		Bullet(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos, PlayerController* bulletController);
		~Bullet();

		void OnUpdate(float deltaTime)override;

		void Init(fw::vec2 pos);
		void SetIsShooting(bool shooting);
		bool GetIsShooting();

	private:
		PlayerController* m_pBulletController;
		bool m_IsShooting;
		bool m_ShootingUp;
		bool m_ShootingLeft;
		bool m_ShootingRight;
		bool m_ShootingDown;
	};

} // namespace fw
