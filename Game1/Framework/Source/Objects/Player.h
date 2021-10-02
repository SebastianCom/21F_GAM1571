#pragma once
#include "Framework.h"

namespace fw {

	class Player : public GameObject
	{
	public:

		Player(fw::FWCore& fwCore);
		~Player();

		void OnUpdate(float deltaTime)override;
		void Draw()override;

	private:
		
		fw::FWCore& m_FWCore;
	};

} // namespace fw
