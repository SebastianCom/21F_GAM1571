#pragma once
#include "Framework.h"
#include "Math/Vector.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include <random>
#include <iostream>


namespace fw {

	float RandomFloat(float min, float max);

	enum class ObjectType
	{
		Player = 1,
		Enemy = 2,
		PickUp = 3,
	};

	class Enemy;

	class GameObject 
	{
	public:

		GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos);
		~GameObject();

		void virtual OnUpdate(float deltaTime);

		void virtual Draw();
		void virtual MoveTo(float deltaTime, fw::vec2 position);
		void virtual SocailDistance(float deltaTime) {};

		void SetX(float x);
		void SetY(float y);
		void SetPosition(fw::vec2 pos);
		
		fw::vec2 GetPosition();

		void SetReadyToDie(bool a);
		bool GetReadyToDie();

		void SetSpeed(float s);
		float GetSpeed();

		void SetObjectType(ObjectType a);
		ObjectType GetObjectType();
		

		float virtual GetRadius();
		void SetRadius(float radius);
		bool  CheckCollision( const GameObject* object);
		bool  CheckCollision(fw::vec2 position, float radius);

		void SetActive(bool a);
		bool GetActive();

		void SetChasing(bool isChasing) { m_Chasing = isChasing; }
		bool GetChasing() { return m_Chasing; }

		void SetScale(float scale) { m_Scale = scale; }
		float GetScale() { return m_Scale; }

		void SetShrinkageTimer(float a);
		void DecrementShrinkageTimer(float a);
		float GetShrinkageTimer();

		fw::vec2 virtual GetPatrolSpotAlpha() { return m_PatrolSpotAlpha; }
		fw::vec2 virtual GetPatrolSpotBeta() { return m_PatrolSpotBeta; };

		void SetMovingToAlpha(bool a) { MovingToAlpha = a; }
		void SetMovingToBeta(bool a) { MovingToBeta = a; }
		bool GetMovingToAlpha() { return MovingToAlpha; }
		bool GetMovingToBeta() { return MovingToBeta; }

	protected:
		
		fw::vec2 m_Position;
		fw::Mesh* m_pMesh;
		fw::ShaderProgram* m_pShader;
		float m_Scale;
		float m_Speed;
		float m_Radius;
		ObjectType m_ObjectType;
		bool m_ReadyToDie;
		bool m_IsActive;
		float m_Shrinkage;
		bool m_Chasing;
		fw::vec2 m_PatrolSpotAlpha;
		fw::vec2 m_PatrolSpotBeta;
		bool MovingToAlpha;
		bool MovingToBeta;
		float m_ColorShift;
		
	};

} // namespace fw
