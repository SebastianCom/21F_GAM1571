
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"

namespace fw {

	GameObject::GameObject()
	{
		m_X = 0;
		m_Y = 0;
		m_Speed = 0;
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

	void GameObject::SetSpeed(float s)
	{
		m_Speed = s;
	}

	float GameObject::GetSpeed()
	{
		return m_Speed;
	}

} // namespace fw
