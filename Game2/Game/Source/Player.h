#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"

class PlayerController;

class Player : public GameObject
{
public:
    Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController);
    virtual ~Player();

    virtual void Update(float deltaTime) override;

    void SetPlayerController(PlayerController* pController) { m_pPlayerController = pController; }

protected:
    PlayerController* m_pPlayerController;
};
