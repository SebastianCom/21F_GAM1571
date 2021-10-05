
#include "Framework.h"

class Game : public fw::GameCore
{
public:
	Game(fw::FWCore& fwCore);
	virtual ~Game();

	void Update(float deltaTime) override;
	void Draw()override;

	void Init();


protected:
	
	fw::FWCore& m_FWCore;

	float m_TimePassed;
	fw::Mesh* m_pPickUpMesh;
	fw::Mesh* m_pPlayerMesh;
	fw::Mesh* m_pEnemyMesh;
	fw::ShaderProgram* m_pPlayerShader;

	fw::ImGuiManager* m_pImGuiManager;

	fw::Player* m_pPlayer;

	std::vector<fw::Enemy*> m_vecEnemies;
	std::vector<fw::PickUp*> m_vecPickUps;

	float m_X;
	float m_Y;

};
