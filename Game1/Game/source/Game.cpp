
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
	m_X = 0;
	m_Y = 0;
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
	m_Meshes["Player"] = new fw::Mesh(GL_TRIANGLES, PLAYER_VERTS);
	m_Meshes["Enemy"] = new fw::Mesh(GL_TRIANGLES, ENEMY1_VERTS);
	m_Meshes["PickUp"] = new fw::Mesh(GL_TRIANGLES, PICKUP_VERTS);
	m_pPlayerController = new fw::PlayerController();
	m_pPlayer = new fw::Player(m_Meshes["Player"], m_pGameObjectShader, fw::vec2(0,0), m_pPlayerController);
	
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
	//if (m_pPlayerController->IsRightHeld())
	//	m_pPlayer->SetX(5 * deltaTime);
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
		
		//Set Enemies Scale
		for (int i = 0; i < m_vecEnemies.size(); i++)
		{
	
			if (m_vecEnemies.at(i)->GetReadyToDie() == true)
			{
				m_vecEnemies.at(i)->SetScale(m_vecEnemies.at(i)->GetShrinkageTimer()); 
			}
			else
			{
				m_vecEnemies.at(i)->SetScale(1);
			}
		}

		//Sets Pick Ups Scale
		for (int i = 0; i < m_vecPickUps.size(); i++)
		{
			
			m_vecPickUps.at(i)->SetScale(m_vecPickUps.at(i)->GetShrinkageTimer());
			
		}
	


	GLint u_Time = glGetUniformLocation(m_pGameObjectShader->GetProgram(), "u_Time");
		glUniform1f(u_Time, m_TimePassed);

	GLint iResolution = glGetUniformLocation(m_pGameObjectShader->GetProgram(), "iResolution");
		glUniform3f(iResolution, static_cast<GLfloat>(m_FWCore.GetWindowWidth()), static_cast<GLfloat>(m_FWCore.GetWindowHeight()), 0);

	GLint iDate = glGetUniformLocation(m_pGameObjectShader->GetProgram(), "iDate");
		glUniform1f(iDate, static_cast<GLfloat>(fw::GetSystemTime()));

	GLint iGlobalTime = glGetUniformLocation(m_pGameObjectShader->GetProgram(), "iGlobalTime");
		glUniform1f(iGlobalTime, static_cast<GLfloat>(fw::GetSystemTimeSinceGameStart()));

	m_pImGuiManager->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
	m_pPlayerController->OnEvent(pEvent);
}



void Game::HandleCollision(float deltaTime)
{
	if (m_pPlayer->GetActive() == true)
	{
		//Collision check against enemies -- MOVE TO FUNCTION
		for (int i = 0; i < m_vecEnemies.size(); i++)
		{
			if (m_vecEnemies.at(i)->GetActive() == true)
			{
				if (m_pPlayer->CheckCollision(m_vecEnemies.at(i), m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y) == true)
				{
					m_pPlayer->SetActive(false);
					m_pPlayer->SetX(m_pPlayer->RandomFloat(-10.0f, 10.0f));
					m_pPlayer->SetY(m_pPlayer->RandomFloat(-10.0f, 10.0f));

					for (int j = 0; j < m_vecEnemies.size(); j++)
					{
						if (m_pPlayer->CheckCollision(m_vecEnemies.at(j), m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y) == true)
						{
							m_pPlayer->SetX(m_pPlayer->RandomFloat(-10.0f, 10.0f));
							m_pPlayer->SetY(m_pPlayer->RandomFloat(-10.0f, 10.0f));
							j = 0;
						}
						m_pPlayer->SetActive(true);
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
					m_vecEnemies.at(i)->DecrementShrinkageTimer(deltaTime);
				}
				else if (m_vecEnemies.at(i)->GetShrinkageTimer() <= 0)
				{
					delete m_vecEnemies.at(i);
					m_vecEnemies.erase(m_vecEnemies.begin() + i);
				}
			}

		}


		//Collision Check against Pick Ups ---- MOVE TO FUNCTION
		for (int i = 0; i < m_vecPickUps.size(); i++)
		{
			if (m_vecPickUps.at(i)->GetActive() == true)
			{
				if (m_pPlayer->CheckCollision(m_vecPickUps.at(i), m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y) == true)
				{
					m_vecPickUps.at(i)->SetReadyToDie(true);
					m_Score += 10;
					m_vecPickUps.at(i)->SetActive(false);
				}
			}

			//Shrinks and Destroys the pick Up
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
	for (int i = 0; i < static_cast<int>(m_pPlayer->RandomFloat(5.0f, 15.0f)); i++)
	{

		m_vecEnemies.push_back(new fw::Enemy(m_Meshes["Enemy"], m_pGameObjectShader, fw::vec2( m_pPlayer->RandomFloat(-10.0f, 10.0f), m_pPlayer->RandomFloat(-10.0f, 10.0f) )));

		//If enemy is spawned on another enemy, it will be moved before being set active.
		if (i > 0)
		{
			for (int j = 0; j < i; j++)
			{
				if (m_vecEnemies.at(i)->CheckCollision(m_vecEnemies.at(j), m_vecEnemies.at(i)->GetPosition().x, m_vecEnemies.at(i)->GetPosition().y) == true || m_vecEnemies.at(i)->CheckCollision(m_pPlayer, m_vecEnemies.at(i)->GetPosition().x, m_vecEnemies.at(i)->GetPosition().y) == true)
				{
					m_vecEnemies.at(i)->SetX(m_pPlayer->RandomFloat(-8.75f, 8.75f));
					m_vecEnemies.at(i)->SetY(m_pPlayer->RandomFloat(-8.75f, 8.75f));
					j = 0;
				}
			}
		}

	}

	for (int i = 0; i < m_vecEnemies.size(); i++)
	{
		m_vecEnemies.at(i)->SetActive(true);
	}


	//Spawn the pick ups
	for (int i = 0; i < static_cast<int>(m_pPlayer->RandomFloat(1.0f, 5.0f)); i++)
	{
		m_vecPickUps.push_back(new fw::PickUp(m_Meshes["PickUp"], m_pGameObjectShader, fw::vec2(m_pPlayer->RandomFloat(-10.0f, 10.0f), m_pPlayer->RandomFloat(-10.0f, 10.0f))));
		m_vecPickUps.at(i)->SetActive(true);


		//If pick is spawned on another pickup, it will be moved 
		if (i > 0)
		{
			for (int j = 0; j < i; j++)
			{
				if (m_vecPickUps.at(i)->CheckCollision(m_vecPickUps.at(j), m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true || m_vecPickUps.at(i)->CheckCollision(m_pPlayer, m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true)
				{
					m_vecPickUps.at(i)->SetX(m_pPlayer->RandomFloat(-8.75f, 8.75f));
					m_vecPickUps.at(i)->SetY(m_pPlayer->RandomFloat(-8.75f, 8.75f));
					j = 0;
				}
			}
		}

		// So Pickups do not spawn on enemies
		for (int j = 0; j < m_vecEnemies.size(); j++)
		{
			if (m_vecPickUps.at(i)->CheckCollision(m_vecEnemies.at(j), m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true || m_vecPickUps.at(i)->CheckCollision(m_pPlayer, m_vecPickUps.at(i)->GetPosition().x, m_vecPickUps.at(i)->GetPosition().y) == true)
			{
				m_vecPickUps.at(i)->SetX(m_pPlayer->RandomFloat(-8.75f, 8.75f));
				m_vecPickUps.at(i)->SetY(m_pPlayer->RandomFloat(-8.75f, 8.75f));
				j = 0;
			}
		}
	}

	m_pPlayer->SetActive(true);

}
