#include "Framework.h"
#include "Game.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "Player.h"
#include "..\Libraries\rapidjson\document.h"


Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
{
    using namespace rapidjson;
    const char* json = fw::LoadCompleteFile("Data/Textures/Sokoban.json", nullptr);
    Document document;
    document.Parse(json);

    // 2. Modify it by DOM.
    Value& widthValue = document["Width"];
    int width = widthValue.GetInt();

    Value& spriteArray = document["Sprites"];
    for (int i = 0; i < spriteArray.Size(); i++)
    {
       Value& sprite = spriteArray[i];
       int x = sprite["X"].GetInt();
    }




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
    m_pTexture = new fw::Texture( "Data/Textures/numbers.png" );

    std::vector<fw::VertexFormat> spriteVerts = {
        { vec2(  0.0f, 0.0f),  255,0,0,255,  vec2(0.0f,0.0f) }, // bl
        { vec2(  0.0f,10.0f),  0,255,0,255,  vec2(0.0f,1.0f) }, // tl
        { vec2( 10.0f,10.0f),  0,0,255,255,  vec2(1.0f,1.0f) }, // tr
        { vec2( 10.0f, 0.0f),  128,128,128,255,  vec2(1.0f,0.0f) }, // br
    };

    m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLE_FAN, spriteVerts );

    m_pPlayerController = new PlayerController();

    m_pGameObject = new GameObject( m_Meshes["Sprite"], m_pBasicShader, vec2(-15.0f,0) );
    m_pPlayer = new Player( m_Meshes["Sprite"], m_pBasicShader, vec2(0,0.0f), m_pPlayerController );
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

    vec2 CamPosition = vec2(0, 0);
    vec2 ProjScale = vec2(0, 0);
    m_pGameObject->Draw(CamPosition, ProjScale);//camPos, projScale,
    m_pPlayer->Draw(CamPosition, ProjScale);

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
