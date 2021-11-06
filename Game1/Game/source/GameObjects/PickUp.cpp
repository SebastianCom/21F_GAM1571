
#include "Framework.h"
#include "Objects/GameObject.h"
#include "PickUp.h"

namespace fw {
	PickUp::PickUp(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos) 
		: GameObject(pMesh, pShader, pos)
	{
		m_Speed = 5;
		SetPosition(pos);
		m_Radius = 0.60f;
		m_ColorShift = 1.0f;
		m_FlashTimer = 0.0f;
		m_IncreaseTimer = false;
	}
	PickUp::~PickUp()
	{
	}
	void PickUp::OnUpdate(float deltaTime)
	{
		ImGui::SliderFloat("Color Shift", &m_FlashTimer, 0.0f, 1.0f);
		Flash(deltaTime);
		m_ColorShift = m_FlashTimer;

		if (GetReadyToDie() == true)
		{
			SetScale(GetShrinkageTimer());
		}
		
	}

	void PickUp::Flash(float deltaTime)
	{
		
		if(m_FlashTimer >= 1.0f)
		{
			m_IncreaseTimer = false;
		}
		else if (m_FlashTimer <= 0.0f)
		{
			m_IncreaseTimer = true;
		}

		if (m_IncreaseTimer)
			m_FlashTimer += deltaTime;
		else 
			m_FlashTimer -= deltaTime;
	}



} // namespace fw
