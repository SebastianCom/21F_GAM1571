#pragma once
#include "../../Libraries/imgui/imgui.h"


namespace fw {

	class CollisionController 
	{
	public:

		CollisionController();
		virtual ~CollisionController();
		void OnEvent(Event* pEvent);
		
	private:
		
		GameObject* m_Object1;
		GameObject* m_Object2;

	};

} // namespace fw
