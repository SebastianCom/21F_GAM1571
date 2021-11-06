
#include "Framework.h"
#include "Game.h"
#include "Constants.h"

Game::Game(fw::FWCore& fwCore)
	:m_FWCore(fwCore)
{

	m_TimePassed = 0.0f;
	m_pGameObjectShader = nullptr;
	m_pImGuiManager = nullptr;
	m_pPlayer = nullptr;
	m_pPlayerController = nullptr;
	m_pCollisionController = nullptr;
	m_Lives = 3;
	m_Score = 0;
	m_ShotCoolDown = 0;
	m_DeltaTime = 0.0f;
	m_Round = 0;

}

Game::~Game()
{
	for (auto& pair : m_Meshes)
	{
		delete pair.second;
	}
	
	delete m_pGameObjectShader;
	delete m_pImGuiManager;
	delete m_pPlayer;
	
	for (int i = 0; i < m_vecEnemies.size(); i++)
	{
		delete m_vecEnemies.at(i);
	}
	m_vecEnemies.clear();

	for (int i = 0; i < m_vecPatrolEnemies.size(); i++)
	{
		delete m_vecPatrolEnemies.at(i);
	}
	m_vecPatrolEnemies.clear();
	
	for (int i = 0; i < m_vecPickUps.size(); i++)
	{
		delete m_vecPickUps.at(i);
	}
	m_vecPickUps.clear();
	
	for (int i = 0; i < m_ActiveGameObjects.size(); i++)
	{
		delete m_ActiveGameObjects.at(i);
	}
	m_ActiveGameObjects.clear();	
	
	for (int i = 0; i < m_vecBullets.size(); i++)
	{
		delete m_vecBullets.at(i);
	}
	m_vecBullets.clear();

	delete m_pPlayerController;
	delete m_pCollisionController;
}

void Game::Init()
{
	//ImGui init
	m_pImGuiManager = new fw::ImGuiManager(&m_FWCore);
	m_pImGuiManager->Init();

	//InitList
	m_pGameObjectShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");
	
	//Create Meshes
	m_Meshes["Player"] = new fw::Mesh(GL_TRIANGLES, PLAYER_VERTS);
	m_Meshes["Enemy"] = new fw::Mesh(GL_TRIANGLES, ENEMY1_VERTS);
	m_Meshes["Enemy2"] = new fw::Mesh(GL_TRIANGLES, ENEMY2_VERTS);
	m_Meshes["PickUp"] = new fw::Mesh(GL_TRIANGLES, PICKUP_VERTS);
	m_Meshes["Bullet"] = new fw::Mesh(GL_TRIANGLES, BULLET_VERTS);
	
	//Create Player controller
	m_pPlayerController = new fw::PlayerController();
	
	//Create Player
	m_pPlayer = new fw::Player(m_Meshes["Player"], m_pGameObjectShader, fw::vec2(0,0), m_pPlayerController);
	
	//Create Enemies and Pick ups
	SpawnGameObjects();

}


void Game::Update(float deltaTime)
{
	//double time = GetSystemTimeSinceGameStart(); another way to do whats below. (Lines 20,21)
	m_DeltaTime = deltaTime;
	m_pImGuiManager->StartFrame(deltaTime);

	//ImGui Winodw Set up
	ImGui::Text("Lives: %d", m_Lives);
	ImGui::Text("Score: %d", m_Score);
	ImGui::Text("Round: %d", m_Round);
	
	if (ImGui::Button(" Round Increase "))
	{
		//int tempsize = m_ActiveGameObjects.size();
		for (int i = m_ActiveGameObjects.size() -1; i > -1; i--)
		{
			
			fw::Enemy* pEnemy = dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.at(i));
			fw::Enemy2* pPatrolEnemy = dynamic_cast<fw::Enemy2*>(m_ActiveGameObjects.at(i));
			fw::PickUp* pPickUp = dynamic_cast<fw::PickUp*>(m_ActiveGameObjects.at(i));
			fw::Bullet* pBullet = dynamic_cast<fw::Bullet*>(m_ActiveGameObjects.at(i));
			if (pEnemy != nullptr)
			{
				m_vecEnemies.push_back(pEnemy);
				m_ActiveGameObjects.pop_back();
			}
			
			else if (pPatrolEnemy != nullptr)
			{
				m_vecPatrolEnemies.push_back(pPatrolEnemy);
				m_ActiveGameObjects.pop_back();
			}
			
			else if (pPickUp != nullptr)
			{
				m_vecPickUps.push_back(pPickUp);
				m_ActiveGameObjects.pop_back();
			}
			
			else if (pBullet != nullptr)
			{
				m_vecBullets.push_back(pBullet);
				m_ActiveGameObjects.pop_back();
			}
			
		}
		m_Round++;
		SpawnGameObjects();
	}
	
	if (ImGui::Button(" Reset to 1 "))
	{
		//int tempsize = m_ActiveGameObjects.size();
		for (int i = m_ActiveGameObjects.size() - 1; i > -1; i--)
		{

			fw::Enemy* pEnemy = dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.at(i));
			fw::Enemy2* pPatrolEnemy = dynamic_cast<fw::Enemy2*>(m_ActiveGameObjects.at(i));
			fw::PickUp* pPickUp = dynamic_cast<fw::PickUp*>(m_ActiveGameObjects.at(i));
			fw::Bullet* pBullet = dynamic_cast<fw::Bullet*>(m_ActiveGameObjects.at(i));
			if (pEnemy != nullptr)
			{
				m_vecEnemies.push_back(pEnemy);
				m_ActiveGameObjects.pop_back();
			}

			else if (pPatrolEnemy != nullptr)
			{
				m_vecPatrolEnemies.push_back(pPatrolEnemy);
				m_ActiveGameObjects.pop_back();
			}

			else if (pPickUp != nullptr)
			{
				m_vecPickUps.push_back(pPickUp);
				m_ActiveGameObjects.pop_back();
			}

			else if (pBullet != nullptr)
			{
				m_vecBullets.push_back(pBullet);
				m_ActiveGameObjects.pop_back();
			}

		}
		m_Round = 1;
		SpawnGameObjects();
	}
	
	//Debugging 


	m_TimePassed += deltaTime;
	double time = m_TimePassed;

	if (m_ShotCoolDown > 0)
	{
		m_ShotCoolDown -= deltaTime;
	}

	m_pPlayer->OnUpdate(deltaTime);

	HandleShooting();

	for (int i = 0; i < m_ActiveGameObjects.size(); i++)
	{
		if (m_ActiveGameObjects.at(i) != nullptr)
		{
			m_ActiveGameObjects.at(i)->OnUpdate(deltaTime);
		}
	}
	
	ImGui::Text("Debugging below");
	ImGui::Text("Enemy 1s Remaining: %d", m_vecEnemies.size());
	ImGui::Text("Enemy 2s Remaining: %d", m_vecPatrolEnemies.size());
	ImGui::Text("Pick Ups Remaining: %d", m_vecPickUps.size());
	ImGui::Text("Active Objects Remaining: %d", m_ActiveGameObjects.size());
	ImGui::Text("Bullets Remaining: %d", m_vecBullets.size());
	ImGui::Text("Player X: %.2f", m_pPlayer->GetPosition().x);
	ImGui::Text("Player Y: %.2f", m_pPlayer->GetPosition().y);

	HandleCollision(deltaTime);
	HandleAI(deltaTime);

	//if (m_ActiveGameObjects.size() == 0 && m_Round > 0)
	//{
	//	m_Round++;
	//	SpawnGameObjects();
	//}
}

void Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
    
	
	m_pPlayer->Draw();

	for(int i = 0; i < m_ActiveGameObjects.size(); i++)
	{
		m_ActiveGameObjects.at(i)->Draw();
	}
	
	m_pImGuiManager->EndFrame();
}

void Game::HandleAI(float deltaTime)
{
	for (int i = 0; i < m_ActiveGameObjects.size(); i++)
	{
		fw::Enemy* pEnemy = dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.at(i));
		if (pEnemy != nullptr)
		{
			if (m_ActiveGameObjects.at(i)->GetChasing())
			{
				if (m_ActiveGameObjects.at(i)->CheckCollision(m_pPlayer) == false)
				{
					if (m_ActiveGameObjects.at(i)->GetReadyToDie() == false)
					{
						if (m_ActiveGameObjects.at(i)->GetPosition().x < 14.2 && m_ActiveGameObjects.at(i)->GetPosition().x > -14.2 &&
							m_ActiveGameObjects.at(i)->GetPosition().y < 14.2 && m_ActiveGameObjects.at(i)->GetPosition().y > -14.2)
						{
							m_ActiveGameObjects.at(i)->MoveTo(deltaTime, m_pPlayer->GetPosition());
							//move enemy towards the player.
						}
						else
						{
							m_ActiveGameObjects.at(i)->SocailDistance(deltaTime);
						}
					}
				}
			}
			for (int j = 0; j < i; j++)
			{
				fw::Enemy* pEnemy2 = dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.at(j));
				if (pEnemy2 != nullptr)
				{
					if (m_ActiveGameObjects.at(i)->CheckCollision(m_ActiveGameObjects.at(j)) == true
						&& m_ActiveGameObjects.at(i)->GetChasing() == true && m_ActiveGameObjects.at(j)->GetChasing() == true)
					{
						if (m_ActiveGameObjects.at(i)->GetReadyToDie() == false)
						{
							m_ActiveGameObjects.at(i)->SetChasing(false);
						}
					}

					if (m_ActiveGameObjects.at(i)->GetChasing() == false && m_ActiveGameObjects.at(i)->GetReadyToDie() == false)
					{
						m_ActiveGameObjects.at(i)->SocailDistance(deltaTime);
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < m_ActiveGameObjects.size(); i++)
	{
		fw::Enemy2* pPatrolEnemy = dynamic_cast<fw::Enemy2*>(m_ActiveGameObjects.at(i));
		if (pPatrolEnemy != nullptr)
		{
			if (m_ActiveGameObjects.at(i)->GetReadyToDie() == false)
			{
				if (m_ActiveGameObjects.at(i)->CheckCollision(m_ActiveGameObjects.at(i)->GetPatrolSpotAlpha(), .8f) == true)
				{
					m_ActiveGameObjects.at(i)->SetMovingToBeta(true);
					m_ActiveGameObjects.at(i)->SetMovingToAlpha(false);

				}
				if (m_ActiveGameObjects.at(i)->CheckCollision(m_ActiveGameObjects.at(i)->GetPatrolSpotBeta(), .8f) == true)
				{
					m_ActiveGameObjects.at(i)->SetMovingToAlpha(true);
					m_ActiveGameObjects.at(i)->SetMovingToBeta(false);
				}

				if (m_ActiveGameObjects.at(i)->GetMovingToBeta() == true)
				{
					m_ActiveGameObjects.at(i)->MoveTo(deltaTime, m_ActiveGameObjects.at(i)->GetPatrolSpotBeta());
				}
				if (m_ActiveGameObjects.at(i)->GetMovingToAlpha() == true)
				{
					m_ActiveGameObjects.at(i)->MoveTo(deltaTime, m_ActiveGameObjects.at(i)->GetPatrolSpotAlpha());
				}
			}
		}
	}
	
}

void Game::HandleShooting()
{
	if (m_pPlayer->IsShooting())
	{
		if (m_ShotCoolDown <= 0)
		{
			if (m_pPlayerController->HasShot() == true)
			{
				SpawnBullet(m_pPlayer->GetPosition());
				m_pPlayerController->SetShot(false);
				m_ShotCoolDown = .25f;
			}
		}
	}
}

void Game::OnEvent(fw::Event* pEvent)
{
	m_pPlayerController->OnEvent(pEvent);

	/*m_pCollisionController = new fw::CollisionController();*/


}



void Game::HandleCollision(float deltaTime) //BROKEN when player moves too quickly they can go through object
{
	//Player on Object Collision
	{
		if (m_pPlayer->GetActive() == true)
		{
			for (int i = 0; i < m_ActiveGameObjects.size(); i++)
			{
				
				if (m_ActiveGameObjects.at(i)->GetActive() == true)
				{
					if (m_pPlayer->CheckCollision(m_ActiveGameObjects.at(i)) == true && m_ActiveGameObjects.at(i)->GetReadyToDie() == false)
					{
						if (m_ActiveGameObjects.back()->GetActive() == true)
						{
							m_ActiveGameObjects.at(i)->SetReadyToDie(true);
							m_ActiveGameObjects.at(i)->SetActive(false);
						}

						fw::Enemy* pEnemy = dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.at(i));
						fw::Enemy2* pPatrolEnemy = dynamic_cast<fw::Enemy2*>(m_ActiveGameObjects.at(i));
						
						if (pEnemy != nullptr || pPatrolEnemy != nullptr)
						{
							m_Lives--;
							m_pPlayer->SetActive(false);
						}
						else
						{
							m_Score += 10;
						}
					}
					if (m_pPlayer->GetActive() == false)
					{
						m_pPlayer->SetPosition(fw::vec2(fw::RandomFloat(-13.75, 13.75), fw::RandomFloat(-13.75, 13.75)));

						bool colliding = true;
						int loopCount = 0;

						while (colliding == true && loopCount < 100)
						{
							m_pPlayer->SetPosition(fw::vec2(fw::RandomFloat(-13.75, 13.75), fw::RandomFloat(-13.75, 13.75)));
							colliding = false;

							for (int j = 0; j < m_ActiveGameObjects.size(); j++)
							{
								if (m_pPlayer->CheckCollision(m_ActiveGameObjects.at(j)) == true)
								{
									colliding = true;
								}

							}
							loopCount++;
						}
						m_pPlayer->SetActive(true);

					}
				}
				
			}

		}

		for (int i = 0; i < m_ActiveGameObjects.size(); i++)
		{
			fw::Bullet* pBullet = dynamic_cast<fw::Bullet*>(m_ActiveGameObjects.at(i));
			for (int j = 0; j < i; j++)
			{
				if (m_ActiveGameObjects.at(i)->CheckCollision(m_ActiveGameObjects.at(j)) == true && m_ActiveGameObjects.at(j)->GetReadyToDie() == false)
				{
				

					if (pBullet != nullptr)
					{
						fw::Enemy* pEnemy = dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.at(j));
						
						if (pEnemy != nullptr)
						{
							m_ActiveGameObjects.at(i)->SetReadyToDie(true);
							m_ActiveGameObjects.at(j)->SetReadyToDie(true);
						}
						
						fw::Enemy2* pPatrolEnemy = dynamic_cast<fw::Enemy2*>(m_ActiveGameObjects.at(j));
						
						if (pPatrolEnemy != nullptr)
						{
							m_ActiveGameObjects.at(i)->SetReadyToDie(true);
							m_ActiveGameObjects.at(j)->SetReadyToDie(true);
						}
						
						fw::PickUp* pPickUp = dynamic_cast<fw::PickUp*>(m_ActiveGameObjects.at(j));

						if (pPickUp != nullptr)
						{
							m_ActiveGameObjects.at(i)->SetReadyToDie(true);
							m_ActiveGameObjects.at(j)->SetReadyToDie(true);
						}
					}
				}
			}
			if (pBullet != nullptr)
			{
				if (m_ActiveGameObjects.at(i)->GetPosition().x >= 15
					|| m_ActiveGameObjects.at(i)->GetPosition().x <= -15
					|| m_ActiveGameObjects.at(i)->GetPosition().y >= 15
					|| m_ActiveGameObjects.at(i)->GetPosition().y <= -15)
				{
					m_ActiveGameObjects.at(i)->SetReadyToDie(true);
				}
			}
		}

	

		if (m_pPlayer->GetActive())
		{
			for (int i = 0; i < m_ActiveGameObjects.size(); i++)
			{
				if (m_ActiveGameObjects.at(i)->GetReadyToDie())
				{

					if (m_ActiveGameObjects.at(i)->GetShrinkageTimer() > 0)
					{
						m_ActiveGameObjects.at(i)->DecrementShrinkageTimer(deltaTime); //m_Shrinkage -= deltatime
					}

					else if (m_ActiveGameObjects.at(i)->GetShrinkageTimer() <= 0) //when the shrink is over is deletes the enemy. Enemy will reflect if not deleted at 0
					{
						fw::GameObject* temp;
						fw::GameObject* temp1;
						temp = m_ActiveGameObjects.at(i);
						temp1 = m_ActiveGameObjects.back();

						m_ActiveGameObjects.at(i) = temp1;
						m_ActiveGameObjects.back() = temp;


						fw::Enemy* pEnemy = dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.back());

						if (pEnemy != nullptr)
						{
							m_vecEnemies.push_back(pEnemy);
						}

						fw::PickUp* pPickUp = dynamic_cast<fw::PickUp*>(m_ActiveGameObjects.back());

						if (pPickUp != nullptr)
						{
							m_vecPickUps.push_back(pPickUp);
						}

						fw::Bullet* pBullet = dynamic_cast<fw::Bullet*>(m_ActiveGameObjects.back());

						if (pBullet != nullptr)
						{
							m_vecBullets.push_back(pBullet);
							m_vecBullets.back()->Init(m_pPlayer->GetPosition());
						}

						fw::Enemy2* pPatrolEnemy = dynamic_cast<fw::Enemy2*>(m_ActiveGameObjects.at(i));
						
						if (pPatrolEnemy != nullptr)
						{
							m_vecPatrolEnemies.push_back(pPatrolEnemy);
						}

						m_ActiveGameObjects.pop_back();
					}
				}
			}
		}


	}//End of Player on Object Collision 
}

void Game::SpawnGameObjects()
{
	for (int i = 0; i < 100; i++)
	{
		//New enemies with mesh from the map, shader, no position.
		m_vecEnemies.push_back(new fw::Enemy(m_Meshes["Enemy"], m_pGameObjectShader, fw::vec2()));
	}
	for (int i = 0; i < 100; i++)
	{
		//New enemies with mesh from the map, shader, no position.
		m_vecPatrolEnemies.push_back(new fw::Enemy2(m_Meshes["Enemy2"], m_pGameObjectShader, fw::vec2()));
	}
	for (int i = 0; i < 20; i++)
	{
		//New enemies with mesh from the map, shader, no position.
		m_vecPickUps.push_back(new fw::PickUp(m_Meshes["PickUp"], m_pGameObjectShader, fw::vec2()));
	}	
	for (int i = 0; i < 100; i++)
	{
		//New enemies with mesh from the map, shader, no position.
		m_vecBullets.push_back(new fw::Bullet(m_Meshes["Bullet"], m_pGameObjectShader, fw::vec2(), m_pPlayerController));
	}

	if (m_Round == 0)
	{
		m_Round++;
	}

	//Vector of Active Game Objects
	if (m_Round == 2)
	{
		for (int i = 0; i < static_cast<int>(fw::RandomFloat(1.0f, 5.0f)); i++) //Get a random number of enemies - static cast so we can use the random float function
		{
			m_ActiveGameObjects.push_back(m_vecPickUps.back());
			m_vecPickUps.pop_back();
		}
		for (int i = 0; i < static_cast<int>(fw::RandomFloat(10.0f, 25.0f)); i++) //Get a random number of enemies - static cast so we can use the random float function
		{
			m_ActiveGameObjects.push_back(m_vecEnemies.back());
			m_vecEnemies.pop_back();
		}
	}
	if (m_Round == 1)
	{
		for (int i = 0; i < static_cast<int>(fw::RandomFloat(1.0f, 5.0f)); i++) //Get a random number of enemies - static cast so we can use the random float function
		{
			m_ActiveGameObjects.push_back(m_vecPickUps.back());
			m_vecPickUps.pop_back();
		}
		for (int i = 0; i < static_cast<int>(fw::RandomFloat(5.0f, 15.0f)); i++) //Get a random number of enemies - static cast so we can use the random float function
		{
			m_ActiveGameObjects.push_back(m_vecPatrolEnemies.back());
			m_vecPatrolEnemies.pop_back();
		}
	}
	if (m_Round == 3)
	{
		for (int i = 0; i < static_cast<int>(fw::RandomFloat(1.0f, 5.0f)); i++) //Get a random number of enemies - static cast so we can use the random float function
		{
			m_ActiveGameObjects.push_back(m_vecPickUps.back());
			m_vecPickUps.pop_back();
		}
		for (int i = 0; i < static_cast<int>(fw::RandomFloat(5.0f, 10.0f)); i++) //Get a random number of enemies - static cast so we can use the random float function
		{
			m_ActiveGameObjects.push_back(m_vecPatrolEnemies.back());
			m_vecPatrolEnemies.pop_back();
		}
		for (int i = 0; i < static_cast<int>(fw::RandomFloat(3.0f, 5.0f)); i++) //Get a random number of enemies - static cast so we can use the random float function
		{
			m_ActiveGameObjects.push_back(m_vecEnemies.back());
			m_vecEnemies.pop_back();
		}
	}

	

	//Spawn Random amount of enemies in random locations
	for (int i = 0; i < m_ActiveGameObjects.size(); i++) //Get a random number of enemies - static cast so we can use the random float function
	{	
		bool colliding = true;
		int loopCount = 0;
		//If enemy is spawned on another enemy or the player, it will be moved before being set active. FLAWED*
		while (colliding && loopCount < 1000)
		{
			m_ActiveGameObjects.at(i)->SetPosition(fw::vec2(fw::RandomFloat(-13.75f, 13.75f), fw::RandomFloat(-13.75f, 13.75f)));

			colliding = false;
			for (int j = 0; j < i; j++)
			{
				if (m_ActiveGameObjects.at(i)->CheckCollision(m_ActiveGameObjects.at(j)) == true
					|| m_ActiveGameObjects.at(i)->CheckCollision(m_pPlayer) == true)
				{
					colliding = true;
				}
			}
			loopCount++;
		}
		if (colliding == true) //Broken?
		{
			m_vecEnemies.push_back(dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.back())); //wrong
			m_ActiveGameObjects.pop_back();
			break; //break only work on for and do while/ while
		}

	}

	for (int i = 0; i < m_ActiveGameObjects.size(); i++) // at this point all enemies should be in unique positions so it is safe to activate them all
	{
		m_ActiveGameObjects.at(i)->SetActive(true);
	}

	m_pPlayer->SetActive(true); // when everything is in place activate the player.
								

}

void Game::SpawnBullet(fw::vec2& position)
{
	m_ActiveGameObjects.push_back(m_vecBullets.back());
	m_vecBullets.pop_back();
	m_ActiveGameObjects.back()->SetPosition(position);
	m_ActiveGameObjects.back()->SetActive(true);

	//activate bullet
}
