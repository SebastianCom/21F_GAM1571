
#include "Framework.h"
#include "PlayerController.h"

namespace fw {

	CollisionController::CollisionController()
	{
		m_Object1 = nullptr;
		m_Object2 = nullptr;
	}

	CollisionController::~CollisionController()
	{
	}

	void CollisionController::OnEvent(Event* pEvent)
	{

		
		if (pEvent->GetEventType() == fw::EventType::Collision)
		{
			fw::Collision* PoE = static_cast<fw::Collision*>(pEvent);
			if (PoE->GetCollisionType() == fw::CollisionType::PlayerOnObject)
			{
				fw::Player* pPlayer = dynamic_cast<fw::Player*>(PoE->GetCollidedObject1());

				fw::Enemy* pEnemy = dynamic_cast<fw::Enemy*>(PoE->GetCollidedObject2());
				fw::Enemy2* pPatrolEnemy = dynamic_cast<fw::Enemy2*>(PoE->GetCollidedObject2());

				if (pEnemy != nullptr || pPatrolEnemy != nullptr)
				{
					pPlayer->DecrementLives();
					PoE->GetCollidedObject1()->SetActive(false);
				}
				else
				{
					pPlayer->IncrementScore();
				}
				PoE->GetCollidedObject2()->SetReadyToDie(true);
				PoE->GetCollidedObject2()->SetActive(false);

				if (PoE->GetCollidedObject1()->GetActive() == false)
				{
					PoE->GetCollidedObject1()->SetPosition(fw::vec2(fw::RandomFloat(-13.75, 13.75), fw::RandomFloat(-13.75, 13.75)));

					bool colliding = true;
					int loopCount = 0;

					while (colliding == true && loopCount < 100)
					{
						PoE->GetCollidedObject1()->SetPosition(fw::vec2(fw::RandomFloat(-13.75, 13.75), fw::RandomFloat(-13.75, 13.75)));
						colliding = false;

						fw::Collision* EoE = static_cast<fw::Collision*>(pEvent);

						if (EoE->GetCollisionType() == fw::CollisionType::EnemyOnObject)
						{
							if (EoE->GetCollidedObject1()->CheckCollision(EoE->GetCollidedObject2()) == true)
							{
								colliding = true;
							}

						}
						loopCount++;
					}
					PoE->GetCollidedObject1()->SetActive(true);

				}
			}


			if (PoE->GetCollisionType() == fw::CollisionType::BulletOnObject)
			{
				fw::Bullet* pBullet = dynamic_cast<fw::Bullet*>(PoE->GetCollidedObject1());
				if (pBullet != nullptr)
				{
					fw::Enemy* pEnemy = dynamic_cast<fw::Enemy*>(PoE->GetCollidedObject2());

					if (pEnemy != nullptr)
					{
						PoE->GetCollidedObject1()->SetReadyToDie(true);
						PoE->GetCollidedObject2()->SetReadyToDie(true);
					}

					fw::Enemy2* pPatrolEnemy = dynamic_cast<fw::Enemy2*>(PoE->GetCollidedObject2());

					if (pPatrolEnemy != nullptr)
					{
						PoE->GetCollidedObject1()->SetReadyToDie(true);
						PoE->GetCollidedObject2()->SetReadyToDie(true);
					}

					fw::PickUp* pPickUp = dynamic_cast<fw::PickUp*>(PoE->GetCollidedObject2());

					if (pPickUp != nullptr)
					{
						PoE->GetCollidedObject1()->SetReadyToDie(true);
						PoE->GetCollidedObject2()->SetReadyToDie(true);
					}


				}
			}
			if (PoE->GetCollisionType() == fw::CollisionType::BulletOnWall)
			{
				PoE->GetCollidedObject1()->SetReadyToDie(true);
			}

		}

	}
	

} // namespace fw
