
#include "Framework.h"

class Game : public fw::GameCore
{
public:
	Game();
	virtual ~Game();

	void Update(float deltaTime) override;
	void Draw()override;

	void Init();


protected:
	float m_TimePassed;
	float m_Greeness;
	fw::Mesh* m_pTestMesh;

};
