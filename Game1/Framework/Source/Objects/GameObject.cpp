
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"


std::random_device seed;
std::mt19937 mersenneTwister(seed());

namespace fw {

	float RandomFloat(float min, float max) //move to random cpp and h
	{
		std::uniform_real_distribution<float> distribution(min, max);
		return distribution(mersenneTwister);
	}

	GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos)
	{

		m_Position = { pos };
		m_pMesh = { pMesh };
		m_pShader = { pShader };
		m_Speed = 0;
		m_Radius = 0;
		m_ReadyToDie = false;
		m_IsActive = false;
		m_ObjectType = ObjectType::Enemny; //spelling error
		m_Shrinkage = 1.0f;
		m_Scale = 1.0f;
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::OnUpdate(float deltaTime)
	{

	}

	void GameObject::Draw()
	{
		m_pMesh->Draw(m_pShader, m_Position, 0.0f, m_Scale);
	}

	void GameObject::SetX(float x)
	{
		m_Position.x = x;
	}

	void GameObject::SetY(float y)
	{
		m_Position.y = y;
	}

	void GameObject::SetPosition(fw::vec2 pos)
	{
		m_Position = pos;
	}

	fw::vec2 GameObject::GetPosition()
	{
		return m_Position;
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



	float GameObject::GetRadius(ObjectType a)
	{ 
		return m_Radius;
	}


	bool GameObject::CheckCollision( const GameObject* object, float x, float y)
	{
		if (object != nullptr)
		{
			float distanceSquared = ((x - object->m_Position.x) * (x - object->m_Position.x) + (y - object->m_Position.y) * (y - object->m_Position.y));
			float radiiSquared = (m_Radius + object->m_Radius) * (m_Radius + object->m_Radius);
			return distanceSquared <= radiiSquared;
		}
		return false;
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
