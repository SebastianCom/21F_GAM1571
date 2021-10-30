
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
	m_Lives = 3;
	m_Score = 0;

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
	m_Meshes["PickUp"] = new fw::Mesh(GL_TRIANGLES, PICKUP_VERTS);
	
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
	
	m_pImGuiManager->StartFrame(deltaTime);

	//ImGui Winodw Set up
	ImGui::Text("Lives: %d", m_Lives);
	ImGui::Text("Score: %d", m_Score);
	ImGui::Text("Enemies Remaining: %d", m_vecEnemies.size());
	ImGui::Text("Pick Ups Remaining: %d", m_vecPickUps.size());
	ImGui::Text("Active Objects Remaining: %d", m_ActiveGameObjects.size());
	ImGui::Text("Player X: %.2f", m_pPlayer->GetPosition().x);
	ImGui::Text("Player Y: %.2f", m_pPlayer->GetPosition().y);


	m_TimePassed += deltaTime;
	double time = m_TimePassed;

	m_pPlayer->OnUpdate(deltaTime);

	//Set Enemies Scale
	//for (int i = 0; i < m_vecEnemies.size(); i++)
	//{
	//	m_vecEnemies.at(i)->OnUpdate(deltaTime);
	//}
	//for (int i = 0; i < m_vecPickUps.size(); i++)
	//{
	//	m_vecPickUps.at(i)->OnUpdate(deltaTime);
	//}
	for (int i = 0; i < m_ActiveGameObjects.size(); i++)
	{
		if (m_ActiveGameObjects.at(i) != nullptr)
		{
			m_ActiveGameObjects.at(i)->OnUpdate(deltaTime);
		}
	}

	//HandleCollision(deltaTime);
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

void Game::OnEvent(fw::Event* pEvent)
{
	m_pPlayerController->OnEvent(pEvent);
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
					if (m_pPlayer->CheckCollision(m_ActiveGameObjects.at(i)) == true)
					{
						if (m_ActiveGameObjects.back()->GetActive() == true)
						{
							m_ActiveGameObjects.at(i)->SetReadyToDie(true);
							m_ActiveGameObjects.at(i)->SetActive(false);
						}

						fw::Enemy* pEnemy = dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.at(i));

						if (pEnemy != nullptr)
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
						m_pPlayer->SetPosition(fw::vec2(fw::RandomFloat(-8.75, 8.75), fw::RandomFloat(-8.75, 8.75)));

						bool colliding = true;
						int loopCount = 0;

						while (colliding == true && loopCount < 100)
						{
							m_pPlayer->SetPosition(fw::vec2(fw::RandomFloat(-8.75, 8.75), fw::RandomFloat(-8.75, 8.75)));
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
	for (int i = 0; i < 20; i++)
	{
		//New enemies with mesh from the map, shader, no position.
		m_vecPickUps.push_back(new fw::PickUp(m_Meshes["PickUp"], m_pGameObjectShader, fw::vec2()));
	}

	//Vector of Active Game Objects
	//m_ActiveGameObjects.push_back(dynamic_cast<fw::Player*>(m_pPlayer));
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

	

	//Spawn Random amount of enemies in random locations
	for (int i = 0; i < m_ActiveGameObjects.size(); i++) //Get a random number of enemies - static cast so we can use the random float function
	{	
		bool colliding = true;
		int loopCount = 0;
		//If enemy is spawned on another enemy or the player, it will be moved before being set active. FLAWED*
		while (colliding && loopCount < 1000)
		{
			m_ActiveGameObjects.at(i)->SetPosition(fw::vec2(fw::RandomFloat(-8.75f, 8.75f), fw::RandomFloat(-8.75f, 8.75f)));

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
			m_vecEnemies.push_back(dynamic_cast<fw::Enemy*>(m_ActiveGameObjects.back()));
			m_ActiveGameObjects.pop_back();
			break; //break only work on for and do while/ while
		}

	}

	for (int i = 0; i < m_ActiveGameObjects.size(); i++) // at this point all enemies should be in unique positions so it is safe to activate them all
	{
		m_ActiveGameObjects.at(i)->SetActive(true);
	}

	m_pPlayer->SetActive(true); // when everything is in place activate the player.

	
								
	//Keeping for one git update as i worte it today. May need it somewhere down the line					
	////Spawn the pick ups
	//for (int i = 0; i < static_cast<int>(fw::RandomFloat(1,5)); i++)
	//{
	//	//New pick up with mesh from the map, shader, random position.
	//	m_vecPickUps.push_back(new fw::PickUp(m_Meshes["PickUp"], m_pGameObjectShader, fw::vec2()));
	//	

	//	bool colliding = true;
	//	int loopCount = 0;
	//	//If enemy is spawned on another enemy or the player, it will be moved before being set active. FLAWED*
	//	while (colliding && loopCount < 1000)
	//	{
	//		m_vecPickUps.at(i)->SetX(fw::RandomFloat(-8.75f, 8.75f));
	//		m_vecPickUps.at(i)->SetY(fw::RandomFloat(-8.75f, 8.75f));

	//		colliding = false;
	//		for (int j = 0; j < i; j++)
	//		{
	//			if (m_vecPickUps.at(i)->CheckCollision(m_vecPickUps.at(j), m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true
	//				|| m_vecPickUps.at(i)->CheckCollision(m_pPlayer, m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true)
	//			{

	//				colliding = true;//***if this happens J will still increment before the next check meaning element 0 will never be checked again
	//			}
	//		}
	//		for (int j = 0; j < m_vecEnemies.size(); j++)
	//		{
	//			if (m_vecPickUps.at(i)->CheckCollision(m_vecEnemies.at(j), m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true)
	//			{

	//				colliding = true;//***if this happens J will still increment before the next check meaning element 0 will never be checked again
	//			}
	//		}

	//		loopCount++;
	//	}

	//	if (colliding == true) //No suitable position, object is deleted
	//	{
	//		delete m_vecPickUps.at(i);
	//		m_vecPickUps.pop_back();
	//		break; //break only work on for and do while/ while
	//	}
	//
	//	m_vecPickUps.at(i)->SetActive(true);

	//}

	

}
