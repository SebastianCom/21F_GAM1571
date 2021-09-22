
#include "Framework.h"
#include "Game.h"

Game::Game()
{
	m_Greeness = 1.0f;
	m_TimePassed = 0.0f;
	m_pTestMesh = nullptr;

}

Game::~Game()
{
	if (m_pTestMesh != nullptr)
	{
		delete m_pTestMesh;
		m_pTestMesh = nullptr;
	}
}

void Game::Update(float deltaTime)
{
	//double time = GetSystemTimeSinceGameStart(); another way to do whats below. (Lines 20,21)

	m_TimePassed += deltaTime;
	double time = m_TimePassed;

	
	
	//m_Greeness = static_cast<float>( abs(sin( time )) ); //faster than the way below
	//m_Greeness = static_cast<float>( sin(time)*0.5 +.5 );


}

void Game::Draw()
{
	glClearColor(0, 0, 0.2, 255);
	glClear(GL_COLOR_BUFFER_BIT);
    m_pTestMesh->Draw();
}

void Game::Init()
{
    m_pTestMesh = new fw::Mesh;
}
