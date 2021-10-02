#pragma once
#include "Framework.h"

namespace fw {
	enum class ObjectType
	{
		Player = 1,
		Enemny = 2,
		PickUp = 3,
	};

	class GameObject : public GameCore
	{
	public:

		GameObject();
		~GameObject();

		void virtual OnUpdate(float deltaTime);

		void virtual Draw();

		void SetX(float x);
		float GetX();

		void SetY(float y);
		float GetY();
		
		void SetSpeed(float s);
		float GetSpeed();

	protected:
		
		float m_X;
		float m_Y;
		float m_Speed;

	};

} // namespace fw
