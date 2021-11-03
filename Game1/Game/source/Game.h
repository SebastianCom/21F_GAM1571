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
	
	void HandleAI(float deltaTime);
	void HandleShooting();

	void Init();

	void HandleCollision(float deltaTime);
	void SpawnGameObjects();
	void SpawnBullet(fw::vec2& position);

protected:
	
	fw::FWCore& m_FWCore;

	float m_TimePassed;
	fw::ShaderProgram* m_pGameObjectShader;

	fw::ImGuiManager* m_pImGuiManager;

	fw::Player* m_pPlayer;

	std::vector<fw::GameObject*> m_ActiveGameObjects;

	std::vector<fw::Enemy*> m_vecEnemies;
	std::vector<fw::PickUp*> m_vecPickUps;
	std::vector<fw::Bullet*> m_vecBullets;
	

	float m_ShotCoolDown;
	int m_Lives;
	int m_Score;

	fw::PlayerController* m_pPlayerController;
	
	std::map<std::string, fw::Mesh*> m_Meshes;




};
