#pragma once
#include "Framework.h"
#include <random>
#include <iostream>


namespace fw {
	enum class ObjectType
	{
		Player = 1,
		Enemny = 2,
		PickUp = 3,
	};

	class Enemy;

	class GameObject 
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
		
		void SetReadyToDie(bool a);
		bool GetReadyToDie();

		void SetSpeed(float s);
		float GetSpeed();

		void SetObjectType(ObjectType a);
		ObjectType GetObjectType();

		float RandomFloat(float min, float max);

		float virtual GetRadius(ObjectType a);
		bool  virtual CheckCollision( const GameObject* object, float x, float y);

		void SetActive(bool a);
		bool GetActive();

		void SetShrinkageTimer(float a);
		void DecrementShrinkageTimer(float a);
		float GetShrinkageTimer();

	protected:
		
		float m_X;
		float m_Y;
		float m_Speed;
		float m_Radius;
		ObjectType m_ObjectType;
		bool m_ReadyToDie;
		bool m_IsActive;
		float m_Shrinkage;
		
	};

} // namespace fw
