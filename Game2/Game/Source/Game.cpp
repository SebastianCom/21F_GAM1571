#include "Framework.h"
#include "Game.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "PathFinder.h"
#include "../Libraries/rapidjson/document.h"
#include <functional>

//int Add(int a, int b)
//{
//    return a + b;
//}
//
//int Sub(int a, int b)
//{
//    return a - b;
//}


typedef int (*MathOperator)(int a, int b);
//typedef std::function<int(int, int)> MathOperator;

//No warnings on rebuild 11/27 5:03pm
Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
{

    //MathOperator op = Add;

    //int a = op(2, 3);

    //op = Sub;

    //int b = op(7, 3);


    //int bp = 1;


    // Init members.
    m_pImGuiManager = nullptr;

    m_pBasicShader = nullptr;
    m_pTexture = nullptr;
    m_pEnemyTexture = nullptr;

    m_pPlayerController = nullptr;

    m_pPlayer = nullptr;
    m_pEnemy = nullptr;

    m_pTileMapGround = nullptr;
    m_pTileMapLevel2 = nullptr;

    m_SafePosition = fw::vec2(0,0);

    CameraPos = vec2(250, 250);
    ProjScale = vec2(1/25.0f, 1/25.0f);
    
  
}

Game::~Game()
{
    delete m_pPlayer;
    delete m_pEnemy;

    delete m_pTileMapGround;
    delete m_pTileMapLevel2;

    delete m_pPlayerController;

    delete m_pTexture;
    delete m_pEnemyTexture;
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
    m_pEnemyTexture = new fw::Texture("Data/Textures/EnemySprites.png");

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

    m_pPlayer = new Player(m_Meshes["Sprite"], m_pBasicShader, m_pTexture, vec2(225, 250), m_pPlayerController); //Spawning offset on the x for debug purposes
    m_pEnemy = new Enemy(m_Meshes["Sprite"], m_pBasicShader, m_pEnemyTexture, vec2(150, 250), m_pTileMapLevel2); //Spawning offset on the x for debug purposes

    PathFinder* path = new PathFinder(m_pTileMapLevel2);
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame(deltaTime);

    m_pPlayer->Update(deltaTime);
    m_pEnemy->Update(deltaTime);

    CheckForCollisions();

   


}

void Game::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    m_pTileMapGround->Draw(CameraPos, ProjScale);
    m_pTileMapLevel2->Draw(CameraPos, ProjScale);
   
    m_pPlayer->Draw(CameraPos, ProjScale);
    m_pEnemy->Draw(CameraPos, ProjScale);

    m_pImGuiManager->EndFrame();
}

void Game::CheckForCollisions()
{
    //Known bug on moveable object if you hold one direction and tap another
    //i had it using a middle point but it didnt look nice and did not colide on corners 
    std::vector<fw::vec2> playerPos;
    playerPos.push_back(m_pPlayer->GetPosition() += fw::vec2(-18, 0)); //TL //18 felt better than 20
    playerPos.push_back(m_pPlayer->GetPosition() += fw::vec2(18, 0));  //TR
    playerPos.push_back(m_pPlayer->GetPosition() += fw::vec2(-18, -20)); //BL
    playerPos.push_back(m_pPlayer->GetPosition() += fw::vec2(18, -20)); //BR
    bool walkable = true;
    
    for (int i = 0; i < playerPos.size(); i++)
    {
        float x = playerPos[i].x / m_pTileMapLevel2->GetTileSize().x;
        float y = playerPos[i].y / m_pTileMapLevel2->GetTileSize().y;
        int playerIndex = int(round(y) * m_pTileMapLevel2->GetTileMapWidth() + round(x)); //floor gets top right
        unsigned char CurrentTile = m_pTileMapLevel2->GetTile(playerIndex);
        walkable = m_pTileMapLevel2->GetTileProperties(CurrentTile).Walkable;
        bool moveable = m_pTileMapLevel2->GetTileProperties(CurrentTile).Moveable;

        if (moveable)//move check
        {
            if (m_pPlayer->GetDirection() == Right)
            {
                unsigned char newIndex = playerIndex + 1;
                unsigned char newTile = m_pTileMapLevel2->GetTile(newIndex);
                if (m_pTileMapLevel2->GetTileProperties(newTile).Walkable == true)
                    m_pTileMapLevel2->SwapTiles(playerIndex, newIndex);
            }
            if (m_pPlayer->GetDirection() == Left)
            {
                unsigned char newIndex = playerIndex - 1;
                unsigned char newTile = m_pTileMapLevel2->GetTile(newIndex);
                if (m_pTileMapLevel2->GetTileProperties(newTile).Walkable == true)
                    m_pTileMapLevel2->SwapTiles(playerIndex, newIndex);
            }
            if (m_pPlayer->GetDirection() == Up)
            {
                unsigned char newIndex = playerIndex + 10;
                unsigned char newTile = m_pTileMapLevel2->GetTile(newIndex);
                if (m_pTileMapLevel2->GetTileProperties(newTile).Walkable == true)
                    m_pTileMapLevel2->SwapTiles(playerIndex, newIndex);
            }
            if (m_pPlayer->GetDirection() == Down)
            {
                unsigned char newIndex = playerIndex - 10;
                unsigned char newTile = m_pTileMapLevel2->GetTile(newIndex);
                if (m_pTileMapLevel2->GetTileProperties(newTile).Walkable == true)
                    m_pTileMapLevel2->SwapTiles(playerIndex, newIndex);
            }
        }
        if (!walkable)
        {
            break;
        }
    }
    if (walkable)
    {
        m_SafePosition = m_pPlayer->GetPosition();
    }
    else if (!walkable)
    {
        m_pPlayer->SetPosition(m_SafePosition);
    }
    playerPos.clear();



}
