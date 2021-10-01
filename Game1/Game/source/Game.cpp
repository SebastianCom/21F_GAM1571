
#include "Framework.h"
#include "Game.h"

Game::Game(fw::FWCore& fwCore)
	:m_FWCore( fwCore)
{
	
	m_Greeness = 1.0f;
	m_TimePassed = 0.0f;
	m_pTestMesh = nullptr;
	m_pBasicShader = nullptr;
	m_pImGuiManager = nullptr;
	m_X = 0;
	m_Y = 0;

	

}

Game::~Game()
{
	delete m_pTestMesh;
	delete m_pBasicShader;
	delete m_pImGuiManager;

}

void Game::Update(float deltaTime)
{
	//double time = GetSystemTimeSinceGameStart(); another way to do whats below. (Lines 20,21)
	
	
	m_pImGuiManager->StartFrame(deltaTime);

	ImGui::ShowDemoWindow();

	ImGui::DragFloat("X", &m_X, 0.01f, -1, 1);

	m_TimePassed += deltaTime;
	double time = m_TimePassed;

	float speed = 0.5f;

	if (m_FWCore.IsKeyDown(VK_RIGHT))
	{
		m_X += speed * deltaTime;
	}
	
	//m_Greeness = static_cast<float>( abs(sin( time )) ); //faster than the way below
	//m_Greeness = static_cast<float>( sin(time)*0.5 +.5 );
	
	
	
	

}

void Game::Draw()
{
	glClearColor(0, 0, 0.2f, 255);
	glClear(GL_COLOR_BUFFER_BIT);
    
	glUseProgram(m_pBasicShader->GetProgram());


	GLint u_Offset = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Offset");
	glUniform2f(u_Offset, m_X, m_Y);

	GLint u_Time = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Time");
	glUniform1f(u_Time, m_TimePassed);
	
	m_pTestMesh->Draw(m_pBasicShader);

	GLint iResolution = glGetUniformLocation(m_pBasicShader->GetProgram(), "iResolution");
	glUniform3f(iResolution, m_FWCore.GetWindowWidth(), m_FWCore.GetWindowHeight(), 0);

	GLint iDate = glGetUniformLocation(m_pBasicShader->GetProgram(), "iDate");
	glUniform1f(iDate, fw::GetSystemTime());

	GLint iGlobalTime = glGetUniformLocation(m_pBasicShader->GetProgram(), "iGlobalTime");
	glUniform1f(iGlobalTime, fw::GetSystemTimeSinceGameStart());

	m_pImGuiManager->EndFrame();
}

void Game::Init()
{
	m_pImGuiManager = new fw::ImGuiManager(&m_FWCore);
	m_pImGuiManager->Init();

    m_pTestMesh = new fw::Mesh;
	m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert","Data/Shaders/Basic.frag");

}
