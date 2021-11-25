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
    virtual void Draw(fw::vec2 camPos, fw::vec2 projScale) override;

    void MoveTheFucker(float deltaTime);

    void SetPlayerController(PlayerController* pController) { m_pPlayerController = pController; }

protected:
    PlayerController* m_pPlayerController;
    fw::vec2 m_PlayerScale;
    float m_Speed;
    std::string m_CurrentSprite;
    float m_AnimTimer;
};
