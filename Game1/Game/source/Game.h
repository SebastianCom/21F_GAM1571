#pragma once
#include "Framework.h"

class Game : public fw::GameCore
{
public:
	Game(fw::FWCore& fwCore);
	virtual ~Game();

	void OnEvent(fw::Event* pEvent) override;
	void Update(float deltaTime) override;
	void Draw()override;
	


	void Init();

	void HandleCollision(float deltaTime);
	void SpawnGameObjects();

protected:
	
	fw::FWCore& m_FWCore;

	float m_TimePassed;
	fw::ShaderProgram* m_pGameObjectShader;

	fw::ImGuiManager* m_pImGuiManager;

	fw::Player* m_pPlayer;

	std::vector<fw::GameObject*> m_ActiveGameObjects;

	std::vector<fw::Enemy*> m_vecEnemies;
	std::vector<fw::PickUp*> m_vecPickUps;

	

	
	int m_Lives;
	int m_Score;

	fw::PlayerController* m_pPlayerController;
	
	std::map<std::string, fw::Mesh*> m_Meshes;



};
