
#include "Framework.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "PickUp.h"

namespace fw {
	PickUp::PickUp(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos) 
		: GameObject(pMesh, pShader, pos)
	{
		m_Speed = 5;
		SetPosition(pos);
		m_Radius = 0.60f;
	}
	PickUp::~PickUp()
	{
	}
	void PickUp::OnUpdate(float deltaTime)
	{


	}

} // namespace fw
