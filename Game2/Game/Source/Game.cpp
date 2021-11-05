#include "Framework.h"
#include "Game.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "Player.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
{
    m_pImGuiManager = nullptr;

    m_pBasicShader = nullptr;
    m_pTexture = nullptr;

    m_pPlayerController = nullptr;

    m_pGameObject = nullptr;
    m_pPlayer = nullptr;
}

Game::~Game()
{
    delete m_pGameObject;
    delete m_pPlayer;

    delete m_pPlayerController;

    delete m_pTexture;
    delete m_pBasicShader;

    for( auto& pair : m_Meshes )
    {
        delete pair.second;
    }

    delete m_pImGuiManager;
}

void Game::Init()
{
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore );
    m_pImGuiManager->Init();

    m_pBasicShader = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );
    m_pTexture = new fw::Texture();

    std::vector<fw::VertexFormat> triangleVerts = {
        { vec2(  0.0f, 0.0f),  255,255,255,255,  vec2(0.0f,0.0f) },
        { vec2( 10.0f,10.0f),  255,255,255,255,  vec2(1.0f,1.0f) },
        { vec2(-10.0f,10.0f),  255,255,255,255,  vec2(0.0f,1.0f) },
    };
    //std::vector<float> diamondVerts = { 0.0f,0.0f,0.2f,   5.0f,5.0f,0.6f,   -5.0f,5.0f,0.9f,   0.0f,10.0f,0.2f   };

    m_Meshes["Triangle"] = new fw::Mesh( GL_TRIANGLES, triangleVerts );
    m_Meshes["Diamond"] = new fw::Mesh( GL_TRIANGLE_STRIP, triangleVerts );

    m_pPlayerController = new PlayerController();

    m_pGameObject = new GameObject( m_Meshes["Diamond"], m_pBasicShader, vec2(-15.0f,0) );
    m_pPlayer = new Player( m_Meshes["Triangle"], m_pBasicShader, vec2(0,0.0f), m_pPlayerController );
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );

    ImGui::ShowDemoWindow();

    m_pGameObject->Update( deltaTime );
    m_pPlayer->Update( deltaTime );

    CheckForCollisions();
}

void Game::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    m_pGameObject->Draw();
    m_pPlayer->Draw();

    m_pImGuiManager->EndFrame();
}

void Game::CheckForCollisions()
{
    if( m_pGameObject->IsCollidingWith( m_pPlayer ) )
    {
        ImGui::Text( "GameObject colliding with Player" );
        // TODO: Handle collisions.
    }
}
