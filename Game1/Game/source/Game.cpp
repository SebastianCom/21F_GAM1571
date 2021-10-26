
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
	ImGui::Text("Player X: %.2f", m_pPlayer->GetPosition().x);
	ImGui::Text("Player Y: %.2f", m_pPlayer->GetPosition().y);


	m_TimePassed += deltaTime;
	double time = m_TimePassed;

	m_pPlayer->OnUpdate(deltaTime);

	//Set Enemies Scale
	for (int i = 0; i < m_vecEnemies.size(); i++)
	{
		m_vecEnemies.at(i)->OnUpdate(deltaTime);
	}

	HandleCollision(deltaTime);
}

void Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
    
	m_pPlayer->Draw();
	
	for (int i = 0; i < m_vecEnemies.size(); i++)
	{
		m_vecEnemies.at(i)->Draw();
	}
	
	for (int i = 0; i < m_vecPickUps.size(); i++)
	{
		m_vecPickUps.at(i)->Draw();
	}
	


	//Sets Pick Ups Scale
	for (int i = 0; i < m_vecPickUps.size(); i++)
	{
		//If Pick Ups at i is ready to die set the scale value to the shrinkage timer.
		m_vecPickUps.at(i)->SetScale(m_vecPickUps.at(i)->GetShrinkageTimer());
		
	}


	m_pImGuiManager->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
	m_pPlayerController->OnEvent(pEvent);
}



void Game::HandleCollision(float deltaTime)
{
	//If the player is active
	if (m_pPlayer->GetActive() == true)
	{
		//loop through enemies
		for (int i = 0; i < m_vecEnemies.size(); i++)
		{
			//make sure enemy is active
			if (m_vecEnemies.at(i)->GetActive() == true)
			{
				//Check player and enemy collision - this needs to be cleaned up now that i use vectors
				if (m_pPlayer->CheckCollision(m_vecEnemies.at(i), m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y) == true)
				{
					m_pPlayer->SetActive(false);
					m_pPlayer->SetX(fw::RandomFloat(-10.0f, 10.0f));
					m_pPlayer->SetY(fw::RandomFloat(-10.0f, 10.0f));

					//Second collision check to ensure the player does not spawn on an enemy
					for (int j = 0; j < m_vecEnemies.size(); j++)
					{
						if (m_pPlayer->CheckCollision(m_vecEnemies.at(j), m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y) == true)
						{
							m_pPlayer->SetX(fw::RandomFloat(-10.0f, 10.0f));
							m_pPlayer->SetY(fw::RandomFloat(-10.0f, 10.0f));
							j = 0; //If there is a collision with an enemy on spawn then the player is moved randomly again and the check is restarted.
						}
						m_pPlayer->SetActive(true); // only after the player spawns in a free space does it become active again
					}

					//Begin Destruction of Enemy
					m_vecEnemies.at(i)->SetReadyToDie(true);
					m_Lives--;
					m_vecEnemies.at(i)->SetActive(false);
				}
			}

			//Makes Enemy Shrink for a second and then disapear
			if (m_vecEnemies.at(i)->GetReadyToDie())
			{
				if (m_vecEnemies.at(i)->GetShrinkageTimer() > 0)
				{
					m_vecEnemies.at(i)->DecrementShrinkageTimer(deltaTime); //m_Shrinkage -= deltatime
				}
				else if (m_vecEnemies.at(i)->GetShrinkageTimer() <= 0) //when the shrink is over is deletes the enemy. Enemy will reflect if not deleted at 0
				{
					delete m_vecEnemies.at(i);
					m_vecEnemies.erase(m_vecEnemies.begin() + i);
				}
			}

		}


		//Collision Check against Pick Ups 
		for (int i = 0; i < m_vecPickUps.size(); i++)
		{
			if (m_vecPickUps.at(i)->GetActive() == true)
			{
				//Checks collision of player and pick up
				if (m_pPlayer->CheckCollision(m_vecPickUps.at(i), m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y) == true)
				{
					m_vecPickUps.at(i)->SetReadyToDie(true);
					m_Score += 10;
					m_vecPickUps.at(i)->SetActive(false);
				}
			}

			//Shrinks and Destroys the pick Up same as enemy... maybe i should make this a function that is called twice.
			if (m_vecPickUps.at(i)->GetReadyToDie())
			{
				if (m_vecPickUps.at(i)->GetShrinkageTimer() > 0)
				{
					m_vecPickUps.at(i)->DecrementShrinkageTimer(deltaTime);
				}
				else if (m_vecPickUps.at(i)->GetShrinkageTimer() <= 0)
				{
					delete m_vecPickUps.at(i);
					m_vecPickUps.erase(m_vecPickUps.begin() + i);
				}
			}
		}
	}
}

void Game::SpawnGameObjects()
{
	//Spawn Random amount of enemies in random locations
	for (int i = 0; i < static_cast<int>(fw::RandomFloat(5.0f, 15.0f)); i++) //Get a random number of enemies - static cast so we can use the random float function
	{
		//New enemies with mesh from the map, shader, random position.
		m_vecEnemies.push_back(new fw::Enemy(m_Meshes["Enemy"], m_pGameObjectShader, fw::vec2()));


		bool colliding = true;
		int loopCount = 0;
		//If enemy is spawned on another enemy or the player, it will be moved before being set active. FLAWED*
		while (colliding && loopCount < 1000)
		{
			m_vecEnemies.at(i)->SetX(fw::RandomFloat(-8.75f, 8.75f));
			m_vecEnemies.at(i)->SetY(fw::RandomFloat(-8.75f, 8.75f));

			colliding = false;
			for (int j = 0; j < i; j++)
			{
				if (m_vecEnemies.at(i)->CheckCollision(m_vecEnemies.at(j), m_vecEnemies.at(i)->GetPosition().x, m_vecEnemies.at(i)->GetPosition().y) == true || m_vecEnemies.at(i)->CheckCollision(m_pPlayer, m_vecEnemies.at(i)->GetPosition().x, m_vecEnemies.at(i)->GetPosition().y) == true)
				{
					
					colliding = true; //***if this happens J will still increment before the next check meaning element 0 will never be checked again
				}

			}
			loopCount++;
		}

		if (colliding == true) //No suitable position, object is deleted
		{
			delete m_vecEnemies.at(i);
			m_vecEnemies.pop_back();
			break; //break only work on for and do while/ while
		}

	}

	for (int i = 0; i < m_vecEnemies.size(); i++) // at this point all enemies should be in unique positions so it is safe to activate them all
	{
		m_vecEnemies.at(i)->SetActive(true);
	}


	//Spawn the pick ups
	for (int i = 0; i < static_cast<int>(fw::RandomFloat(1.0f, 5.0f)); i++)
	{
		//New pick up with mesh from the map, shader, random position.
		m_vecPickUps.push_back(new fw::PickUp(m_Meshes["PickUp"], m_pGameObjectShader, fw::vec2(fw::RandomFloat(-10.0f, 10.0f), fw::RandomFloat(-10.0f, 10.0f))));
		

		//If pick is spawned on another pickup, it will be moved 
		if (i > 0)
		{
			for (int j = 0; j < i; j++)
			{
				if (m_vecPickUps.at(i)->CheckCollision(m_vecPickUps.at(j), m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true || m_vecPickUps.at(i)->CheckCollision(m_pPlayer, m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true)
				{
					m_vecPickUps.at(i)->SetX(fw::RandomFloat(-8.75f, 8.75f));
					m_vecPickUps.at(i)->SetY(fw::RandomFloat(-8.75f, 8.75f));
					j = 0;
				}
			}
		}

		// So Pickups do not spawn on enemies
		for (int j = 0; j < m_vecEnemies.size(); j++)
		{
			if (m_vecPickUps.at(i)->CheckCollision(m_vecEnemies.at(j), m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true || m_vecPickUps.at(i)->CheckCollision(m_pPlayer, m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true)
			{
				m_vecPickUps.at(i)->SetX(fw::RandomFloat(-8.75f, 8.75f));
				m_vecPickUps.at(i)->SetY(fw::RandomFloat(-8.75f, 8.75f));
				j = 0;
			}
		}
		
		m_vecPickUps.at(i)->SetActive(true);

	}

	m_pPlayer->SetActive(true); // when everything is in place activate the player.

}
