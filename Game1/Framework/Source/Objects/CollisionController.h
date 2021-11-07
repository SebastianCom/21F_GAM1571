#pragma once
#include "../../Libraries/imgui/imgui.h"


namespace fw {

	class CollisionController 
	{
	public:

		CollisionController();
		virtual ~CollisionController();
		//void OnEvent(Event* pEvent, GameObject* Object1, GameObject* Object2);
		//void OnEvent(Event* pEvent, Player* player, GameObject* Object2);
		void OnEvent(Event* pEvent);
		bool CheckCollision();
		
	private:
		
		GameObject* m_Object1;
		GameObject* m_Object2;

		bool m_Collision;
	};

} // namespace fw
