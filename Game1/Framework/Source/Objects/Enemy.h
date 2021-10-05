#pragma once
#include "Framework.h"

namespace fw {

	class Enemy : public GameObject
	{
	public:

		Enemy(float X, float Y);
		~Enemy();

		void OnUpdate(float deltaTime)override;
		void Draw()override;
	
	private:
		
		fw::FWCore& m_FWCore;
	};

} // namespace fw
