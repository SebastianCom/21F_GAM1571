
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "PickUp.h"

namespace fw {
	PickUp::PickUp(float X, float Y)
	{
		m_Speed = 5;
		SetX(X);
		SetY(Y);
		m_Radius = 0.80f;
	}
	PickUp::~PickUp()
	{
	}
	void PickUp::OnUpdate(float deltaTime)
	{


	}
	void PickUp::Draw()
	{
	}
} // namespace fw
