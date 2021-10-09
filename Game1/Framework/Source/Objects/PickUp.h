#pragma once
#include "Framework.h"

namespace fw {

	class PickUp : public GameObject
	{
	public:

		PickUp(float X, float Y);
		~PickUp();

		void OnUpdate(float deltaTime)override;
		void Draw()override;

	private:
		
	};

} // namespace fw
