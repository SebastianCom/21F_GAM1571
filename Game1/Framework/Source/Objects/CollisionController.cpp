
#include "Framework.h"
#include "PlayerController.h"

namespace fw {

	CollisionController::CollisionController()
	{
		m_Object1 = nullptr;
		m_Object2 = nullptr;
		m_Collision = false;
	}

	CollisionController::~CollisionController()
	{
	}

	void CollisionController::OnEvent(Event* pEvent, GameObject* Object1, GameObject* Object2)
	{

		m_Object1 = Object1;
		m_Object2 = Object2;
	}

	void CollisionController::OnEvent(Event* pEvent, Player* player, GameObject* Object2)
	{
		m_Object1 = player;
		m_Object2 = Object2;
	}

	bool CollisionController::CheckCollision()
	{
		if (m_Object1 != nullptr)
		{
			float distanceSquared = (((m_Object1->GetPosition().x - m_Object2->GetPosition().x) * (m_Object1->GetPosition().x - m_Object2->GetPosition().x)) + ((m_Object1->GetPosition().y - m_Object2->GetPosition().y) * (m_Object1->GetPosition().y - m_Object2->GetPosition().y)));
			float radiiSquared = (m_Object1->GetRadius() + m_Object2->GetRadius()) * (m_Object1->GetRadius() + m_Object2->GetRadius());
			if (distanceSquared <= radiiSquared)
			{
				m_Collision = true;
			}
		}
		else
		{
			m_Collision = false;
		}
		return m_Collision;
	}

} // namespace fw
