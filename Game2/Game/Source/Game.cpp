#include "Framework.h"
#include "Game.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "Player.h"
#include "../Libraries/rapidjson/document.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
{
    //// Load json spritesheet.
    //const char* json = fw::LoadCompleteFile( "Data/Textures/Sokoban.json", nullptr );
    //rapidjson::Document document;
    //document.Parse( json );
    //delete[] json;

    //rapidjson::Value& widthValue = document["Width"];
    //int width = widthValue.GetInt();

    //rapidjson::Value& spriteArray = document["Sprites"];
    //for( rapidjson::SizeType i=0; i<spriteArray.Size(); i++ )
    //{
    //    rapidjson::Value& sprite = spriteArray[i];
    //    int x = sprite["X"].GetInt();
    //    int bp = 1;
    //}

    // Init members.
    m_pImGuiManager = nullptr;

    m_pBasicShader = nullptr;
    m_pTexture = nullptr;
    m_pTexture2 = nullptr;

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
    // OpenGL settings.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore );
    m_pImGuiManager->Init();

    m_pBasicShader = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );
    m_pTexture = new fw::Texture();
    m_pTexture2 = new fw::Texture( "Data/Textures/Sprites.png" );

	//"Width":	512,
	//"Height":	512,
    //"Name":	"ground_05",
    //    "X":	195,
    //    "Y":	448,
    //    "W":	64,
    //    "H":	64

    std::vector<fw::VertexFormat> spriteVerts = {
        { vec2(  0.0f, 0.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bl // * vec2(64/512.0f,64/512.0f) + vec2(195/512.0f,448/512.0f) }, // bl
        { vec2(  0.0f,10.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // tl // * vec2(64/512.0f,64/512.0f) + vec2(195/512.0f,448/512.0f) }, // tl
        { vec2( 10.0f,10.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // tr // * vec2(64/512.0f,64/512.0f) + vec2(195/512.0f,448/512.0f) }, // tr
        { vec2( 10.0f, 0.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // br // * vec2(64/512.0f,64/512.0f) + vec2(195/512.0f,448/512.0f) }, // br
    };

    m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLE_FAN, spriteVerts );

    m_pPlayerController = new PlayerController();

    m_pGameObject = new GameObject( m_Meshes["Sprite"], m_pBasicShader, m_pTexture, vec2(-100.0f,-10.0f) );
    m_pPlayer = new Player( m_Meshes["Sprite"], m_pBasicShader, m_pTexture2, vec2(0,0), m_pPlayerController );
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
