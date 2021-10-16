#pragma once

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

	private:
		bool m_right;
		bool m_left;
		bool m_up;
		bool m_down;
	};

} // namespace fw
