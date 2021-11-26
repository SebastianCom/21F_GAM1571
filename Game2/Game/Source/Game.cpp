#include "Framework.h"
#include "Game.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "Player.h"
#include "TileMap.h"
#include "../Libraries/rapidjson/document.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
{

    // Init members.
    m_pImGuiManager = nullptr;

    m_pBasicShader = nullptr;
    m_pTexture = nullptr;

    m_pPlayerController = nullptr;

    m_pPlayer = nullptr;

    m_pTileMapGround = nullptr;
    m_pTileMapLevel2 = nullptr;

    m_SafePosition = fw::vec2(0, 0);

    CameraPos = vec2(250, 250);
    ProjScale = vec2(1/25.0f, 1/25.0f);
    
}

Game::~Game()
{
    delete m_pPlayer;

    delete m_pTileMapGround;
    delete m_pTileMapLevel2;

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
    m_pTexture = new fw::Texture("Data/Textures/Sprites.png");

    std::vector<fw::VertexFormat> spriteVerts = {
        { vec2(  0.0f, 0.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bl // * vec2(64/512.0f,64/512.0f) + vec2(195/512.0f,448/512.0f) }, // bl
        { vec2(  0.0f,10.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // tl // * vec2(64/512.0f,64/512.0f) + vec2(195/512.0f,448/512.0f) }, // tl
        { vec2( 10.0f,10.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // tr // * vec2(64/512.0f,64/512.0f) + vec2(195/512.0f,448/512.0f) }, // tr
        { vec2( 10.0f, 0.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // br // * vec2(64/512.0f,64/512.0f) + vec2(195/512.0f,448/512.0f) }, // br
    };

    m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLE_FAN, spriteVerts );

    m_pPlayerController = new PlayerController();

    
    
    m_pTileMapGround = new TileMap(m_Meshes["Sprite"], m_pBasicShader, m_pTexture,1);
    m_pTileMapLevel2 = new TileMap(m_Meshes["Sprite"], m_pBasicShader, m_pTexture,2);

    m_pPlayer = new Player(m_Meshes["Sprite"], m_pBasicShader, m_pTexture, vec2(225, 250), m_pPlayerController);

    //fw::vec2 test = m_pPlayer->m_pSpriteSheet->GetSpriteInfo(m_pPlayer->m_Sprites["Player Down"]).UVOffset;


}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame(deltaTime);

    ImGui::ShowDemoWindow();

    m_pPlayer->Update(deltaTime);

    CheckForCollisions();

    const int num = 15;


}

void Game::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    m_pTileMapGround->Draw(CameraPos, ProjScale);
    m_pTileMapLevel2->Draw(CameraPos, ProjScale);
   
    m_pPlayer->Draw(CameraPos, ProjScale);

    m_pImGuiManager->EndFrame();
}

void Game::CheckForCollisions()
{
    fw::vec2 playerPos = m_pPlayer->GetPosition();

    float x = playerPos.x / m_pTileMapLevel2->GetTileSize();
    float y = playerPos.y / m_pTileMapLevel2->GetTileSize();
    int playerIndex = int(round(y) * m_pTileMapLevel2->GetTileMapWidth() + round(x)); //floor gets top right
    
    ImGui::DragInt("Index", &playerIndex, 0, 100);
    
    unsigned char CurrentTile = m_pTileMapLevel2->GetTile(playerIndex);
    
    int IntCurrentTile = int(CurrentTile);
    ImGui::DragInt("Index", &IntCurrentTile, 0, 100);
    
    bool walkable = m_pTileMapLevel2->GetTileProperties(CurrentTile).Walkable;
    
    if (walkable)
    {
        m_SafePosition = m_pPlayer->GetPosition();
        ImGui::Text("Walkable");
    }
    else if (!walkable)
    {
        m_pPlayer->SetPosition(m_SafePosition);
        ImGui::Text("Not Walkable");
    }
}
