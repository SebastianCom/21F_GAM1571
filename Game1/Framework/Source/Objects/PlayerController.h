#pragma once
#include "../../Libraries/imgui/imgui.h"

namespace fw {

	class PlayerController 
	{
	public:

		PlayerController();
		virtual ~PlayerController();
		void OnEvent(Event* pEvent);
		bool IsRight() { return m_right; }
		bool IsLeft() { return m_left; }
		bool IsUp() { return m_up; }
		bool IsDown() { return m_down; }
		bool ShootingRight() { return m_shootright; }
		bool ShootingLeft() { return m_shootleft; }
		bool ShootingUp() { return m_shootup; }
		bool ShootingDown() { return m_shootdown; }
		bool HasShot() { return m_Shot;  }
		void SetShot(bool hasShot);

	private:
		bool m_right;
		bool m_left;
		bool m_up;
		bool m_down;
		
		bool m_shootup;
		bool m_shootleft;
		bool m_shootdown;
		bool m_shootright;

		bool m_Shot;
	};

} // namespace fw
