
#include "Framework.h"
#include "Game.h"

Game::Game(fw::FWCore& fwCore)
	:m_FWCore(fwCore)
{

	m_TimePassed = 0.0f;
	m_pPickUpMesh = nullptr;
	m_pPlayerMesh = nullptr;
	m_pEnemyMesh = nullptr;
	m_pPlayerShader = nullptr;
	m_pEnemyShader = nullptr;
	m_pImGuiManager = nullptr;
	m_pPlayer = nullptr;
	m_vecEnemies = {nullptr};
	m_vecPickUps = { nullptr };
	m_X = 0;
	m_Y = 0;
	m_Lives = 3;
	m_Score = 0;
	m_Shrinkage = 1.0f;


	

	

}

Game::~Game()
{
	delete m_pPickUpMesh;
	delete m_pPlayerShader;
	delete m_pImGuiManager;
	delete m_pPlayerMesh;
	delete m_pEnemyMesh;
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

void Game::Update(float deltaTime)
{
	//double time = GetSystemTimeSinceGameStart(); another way to do whats below. (Lines 20,21)
	
	m_pImGuiManager->StartFrame(deltaTime);

	ImGui::Text("Lives: %d", m_Lives);
	ImGui::Text("Score: %d", m_Score);
	ImGui::Text("Enemies Remaining: %d", m_vecEnemies.size());
	ImGui::Text("Pick Ups Remaining: %d", m_vecPickUps.size());


	m_TimePassed += deltaTime;
	double time = m_TimePassed;

	m_pPlayer->OnUpdate(deltaTime);


	for (int i = 0; i < m_vecEnemies.size(); i++)
	{
		if (m_vecEnemies.at(i)->GetActive() == true)
		{
			if (m_pPlayer->CheckCollision(m_vecEnemies.at(i), m_pPlayer->GetX(), m_pPlayer->GetY()) == true)
			{

				for (int i = 0; i < 1; i++)
				{
					m_pPlayer->SetX(m_pPlayer->RandomFloat(-10.0f, 10.0f));
					m_pPlayer->SetY(m_pPlayer->RandomFloat(-10.0f, 10.0f));
					if (m_pPlayer->CheckCollision(m_vecEnemies.at(i), m_pPlayer->GetX(), m_pPlayer->GetY()) == true || m_pPlayer->CheckCollision(m_vecPickUps.at(i), m_pPlayer->GetX(), m_pPlayer->GetY()) == true)
					{
						i--;
					}
				}
				m_vecEnemies.at(i)->SetReadyToDie(true);
				m_Lives--;
				m_vecEnemies.at(i)->SetActive(false);
			}
		}
			if (m_vecEnemies.at(i)->GetReadyToDie())
			{
				if (m_Shrinkage > 0)
				{
					m_Shrinkage -= deltaTime;
				}
				else if (m_Shrinkage <= 0)
				{
					delete m_vecEnemies.at(i);
					m_vecEnemies.erase(m_vecEnemies.begin() + i);
					m_Shrinkage = 1;
				}
			}

	}
	
	for (int i = 0; i < m_vecPickUps.size(); i++)
	{
		if (m_pPlayer->CheckCollision(m_vecPickUps.at(i), m_pPlayer->GetX(), m_pPlayer->GetY()) == true)
		{

			delete m_vecPickUps.at(i);
			m_vecPickUps.erase(m_vecPickUps.begin() + i);
			m_Score += 10;
			i--;
		}
	}

	
	

}

void Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
    
	glUseProgram(m_pPlayerShader->GetProgram());

	
	GLint u_Offset = glGetUniformLocation(m_pPlayerShader->GetProgram(), "u_Offset");
	GLint u_Scale = glGetUniformLocation(m_pEnemyShader->GetProgram(), "u_Scale");
	
		
		glUniform2f(u_Offset, m_pPlayer->GetX(), m_pPlayer->GetY());
		glUniform1f(u_Scale, 1);
		m_pPlayerMesh->Draw(m_pPlayerShader);
		
		for (int i = 0; i < m_vecEnemies.size(); i++)
		{
			
			if (m_vecEnemies.at(i) != nullptr)
			{
				if (m_vecEnemies.at(i)->GetReadyToDie() == true)
				{
					glUniform1f(u_Scale, m_Shrinkage);
				}
				else
				{
					glUniform1f(u_Scale, 1);
				}
				
				glUniform2f(u_Offset, m_vecEnemies.at(i)->GetX(), m_vecEnemies.at(i)->GetY());
				
				m_pEnemyMesh->Draw(m_pEnemyShader);
			}

		}
		for (int i = 0; i < m_vecPickUps.size(); i++)
		{
			if (m_vecPickUps.at(i) != nullptr)
			{
				glUniform2f(u_Offset, m_vecPickUps.at(i)->GetX(), m_vecPickUps.at(i)->GetY());
				glUniform1f(u_Scale, 1);
				m_pPickUpMesh->Draw(m_pPlayerShader);
			}
		}
	
	GLint u_Time = glGetUniformLocation(m_pPlayerShader->GetProgram(), "u_Time");
		glUniform1f(u_Time, m_TimePassed);
	

	GLint iResolution = glGetUniformLocation(m_pPlayerShader->GetProgram(), "iResolution");
		glUniform3f(iResolution, m_FWCore.GetWindowWidth(), m_FWCore.GetWindowHeight(), 0);

	GLint iDate = glGetUniformLocation(m_pPlayerShader->GetProgram(), "iDate");
		glUniform1f(iDate, fw::GetSystemTime());

	GLint iGlobalTime = glGetUniformLocation(m_pPlayerShader->GetProgram(), "iGlobalTime");
		glUniform1f(iGlobalTime, fw::GetSystemTimeSinceGameStart());

	m_pImGuiManager->EndFrame();
}

void Game::Init()
{
	m_pImGuiManager = new fw::ImGuiManager(&m_FWCore);
	m_pImGuiManager->Init();

	m_pPickUpMesh = new fw::Mesh(fw::ObjectType::PickUp);
	m_pPlayerMesh = new fw::Mesh(fw::ObjectType::Player);
	m_pEnemyMesh = new fw::Mesh(fw::ObjectType::Enemny);
	m_pPlayerShader = new fw::ShaderProgram("Data/Shaders/Basic.vert","Data/Shaders/Basic.frag");
	m_pEnemyShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");
	m_pPlayer = new fw::Player(m_FWCore);

	//Honestly i got stuck here. Depending on how long the program took to start up 1 - 3 enemies were null when accessing the fw core and threw off the whole thing
	for (int i = 0; i < static_cast<int>(m_vecEnemies.at(0)->RandomFloat(1.0f, 15.0f) + 3); i++)
	{
		m_vecEnemies.push_back(new fw::Enemy(m_vecEnemies.at(i)->RandomFloat(-8.75f, 8.75f), m_vecEnemies.at(i)->RandomFloat(-10.0f, 10.0f)));
		
		//Make sure player does not spawn on enemy
		if (m_pPlayer->CheckCollision(m_vecEnemies.at(i), m_pPlayer->GetX(), m_pPlayer->GetY()) == true)
		{

			delete m_vecEnemies.at(i);
			m_vecEnemies.erase(m_vecEnemies.begin() + i);
			i--;
		}

	}
	m_vecEnemies.erase(m_vecEnemies.begin()); m_vecEnemies.erase(m_vecEnemies.begin()); m_vecEnemies.erase(m_vecEnemies.begin());

	for (int i = 0; i < static_cast<int>(m_vecPickUps.at(0)->RandomFloat(1.0f, 5.0f)); i++)
	{
		m_vecPickUps.push_back(new fw::PickUp(m_vecPickUps.at(i)->RandomFloat(-10.0f, 10.0f), m_vecPickUps.at(i)->RandomFloat(-10.0f, 10.0f)));
	}
	
	for (int i = 0; i < m_vecEnemies.size(); i++)
	{
		m_vecEnemies.at(i)->SetActive(true);
		if (i >= 1 && m_vecEnemies.at(i)->CheckCollision(m_vecEnemies.at(i - 1.0), m_vecEnemies.at(i)->GetX(), m_vecEnemies.at(i)->GetY()) == true)
		{
			m_vecEnemies.at(i)->SetX(m_vecEnemies.at(i)->RandomFloat(-8.75f, 8.75f));
			m_vecEnemies.at(i)->SetY(m_vecEnemies.at(i)->RandomFloat(-8.75f, 8.75f));
			i--;
		}
	}
	// Todo set enemy inactive while player respawns
}
