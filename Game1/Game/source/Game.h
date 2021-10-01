
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
	float m_Greeness;
	fw::Mesh* m_pTestMesh;
	fw::ShaderProgram* m_pBasicShader;

	fw::ImGuiManager* m_pImGuiManager;

	float m_X;
	float m_Y;

};
