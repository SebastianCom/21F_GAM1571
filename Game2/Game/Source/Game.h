#pragma once

#include "Framework.h"
#include "DataTypes.h"


class PlayerController;
class GameObject;
class SpriteSheet;
class TileMap;
class Player;
class Enemy;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore& fwCore);
    virtual ~Game();

    void Init();
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void CheckForCollisions();

protected:
    fw::FWCore& m_FWCore;

    fw::ImGuiManager* m_pImGuiManager;

    std::map<std::string, fw::Mesh*> m_Meshes;
    fw::ShaderProgram* m_pBasicShader;
    fw::Texture* m_pTexture;
    fw::Texture* m_pEnemyTexture;

    PlayerController* m_pPlayerController;


    Player* m_pPlayer;
    Enemy* m_pEnemy;
    Enemy* m_pEnemy2;

    TileMap* m_pTileMapGround;
    TileMap* m_pTileMapLevel2;

    fw::vec2 CameraPos;
    fw::vec2 ProjScale;
    
    fw::vec2 m_SafePosition;

};
