
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"


std::random_device seed;
std::mt19937 mersenneTwister(seed());

namespace fw {

	GameObject::GameObject()
	{
		m_X = 0;
		m_Y = 0;
		m_Speed = 0;
		m_Radius = 0;
		m_ReadyToDie = false;
		m_IsActive = false;
		m_ObjectType = ObjectType::Enemny;
		m_Shrinkage = 1.0f;
		
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::OnUpdate(float deltaTime)
	{

	}

	void GameObject::Draw()
	{
	}

	void GameObject::SetX(float x)
	{
		m_X = x;
	}

	float GameObject::GetX()
	{
		return m_X;
	}

	void GameObject::SetY(float y)
	{
		m_Y = y;
	}

	float GameObject::GetY()
	{
		return m_Y;
	}

	void GameObject::SetReadyToDie(bool a)
	{
		m_ReadyToDie = a;
	}

	bool GameObject::GetReadyToDie()
	{
		return m_ReadyToDie;
	}

	void GameObject::SetSpeed(float s)
	{
		m_Speed = s;
	}

	float GameObject::GetSpeed()
	{
		return m_Speed;
	}

	void GameObject::SetObjectType(ObjectType a)
	{
		m_ObjectType = a;
	}

	ObjectType GameObject::GetObjectType()
	{
		return m_ObjectType;
	}

	float GameObject::RandomFloat(float min, float max)
	{
		std::uniform_real_distribution<float> distribution(min, max);
		return distribution(mersenneTwister);
	}

	float GameObject::GetRadius(ObjectType a)
	{ 
		return m_Radius;
	}


	bool GameObject::CheckCollision( const GameObject* object, float x, float y)
	{
		if (object != nullptr)
		{
			float distanceSquared = ((x - object->m_X) * (x - object->m_X) + (y - object->m_Y) * (y - object->m_Y));
			float radiiSquared = (m_Radius + object->m_Radius) * (m_Radius + object->m_Radius);
			return distanceSquared <= radiiSquared;
		}
	}

	void GameObject::SetActive(bool a)
	{
		m_IsActive = a;
	}

	bool GameObject::GetActive()
	{
		return m_IsActive;
	}

	void GameObject::SetShrinkageTimer(float a)
	{
		m_Shrinkage = a;
	}

	void GameObject::DecrementShrinkageTimer(float a)
	{
		m_Shrinkage -= a;
	}

	float GameObject::GetShrinkageTimer()
	{
		return m_Shrinkage;
	}

} // namespace fw
