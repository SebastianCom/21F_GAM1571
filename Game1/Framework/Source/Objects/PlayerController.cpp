
#include "Framework.h"
#include "PlayerController.h"

namespace fw {



	PlayerController::PlayerController()
	{
		m_right = false;
		m_left = false;
		m_up = false;
		m_down = false;
	}

	PlayerController::~PlayerController()
	{
	}

	void PlayerController::OnEvent(Event* pEvent)
	{
		if (pEvent->GetEventType() == fw::EventType::Input)
		{
			fw::InputEvent* pInputEvent = static_cast<InputEvent*>(pEvent);
			if (pInputEvent->GetInputDeviceType() == fw::DeviceType::Keyboard)
			{
				if (pInputEvent->GetInputState() == fw::InputState::Pressed)
				{
					if (pInputEvent->GetID() == VK_RIGHT || pInputEvent->GetID() == 'D')
					{
						m_right = true;
					}
					if (pInputEvent->GetID() == VK_LEFT || pInputEvent->GetID() == 'A')
					{
						m_left = true;
					}
					if (pInputEvent->GetID() == VK_UP || pInputEvent->GetID() == 'W')
					{
						m_up = true;
					}
					if (pInputEvent->GetID() == VK_DOWN || pInputEvent->GetID() == 'S')
					{
						m_down = true;
					}
				}
			}

			if (pInputEvent->GetInputDeviceType() == fw::DeviceType::Keyboard)
			{
				if (pInputEvent->GetInputState() == fw::InputState::Released)
				{
					if (pInputEvent->GetID() == VK_RIGHT || pInputEvent->GetID() == 'D')
					{
						m_right = false;
					}
					if (pInputEvent->GetID() == VK_LEFT || pInputEvent->GetID() == 'A')
					{
						m_left = false;
					}
					if (pInputEvent->GetID() == VK_UP || pInputEvent->GetID() == 'W')
					{
						m_up = false;
					}
					if (pInputEvent->GetID() == VK_DOWN || pInputEvent->GetID() == 'S')
					{
						m_down = false;
					}
				}
			}
		}
	}

} // namespace fw
