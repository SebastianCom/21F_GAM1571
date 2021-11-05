#pragma once

#include "Framework.h"
#include "DataTypes.h"

class PlayerController;
class GameObject;

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

    PlayerController* m_pPlayerController;

    GameObject* m_pGameObject;
    GameObject* m_pPlayer;
};
