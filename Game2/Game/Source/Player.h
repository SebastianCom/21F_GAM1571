#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"

class PlayerController;
class TileMap;

enum Direction
{
    Up, //0
    Down,
    Left,
    Right,
    NumDirections,
};

class Player : public GameObject
{
public:
    Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController, TileMap* pMap);
    virtual ~Player();

    virtual void Update(float deltaTime) override;
    virtual void Draw(fw::vec2 camPos, fw::vec2 projScale) override;

    void MoveTheFucker(float deltaTime);
    void MoveTheBox();
    
    fw::vec2 GetPosition();
    void SetPosition(fw::vec2 pos);
    void SetPlayerController(PlayerController* pController) { m_pPlayerController = pController; }

    unsigned char GetDirection() { return m_PlayerDirection; }

    void PullBlocks(int x, int y); // REMINDER: i want coords not world 
    void PushBlocks(int x, int y);

protected:
    PlayerController* m_pPlayerController;
    fw::vec2 m_PlayerScale;
    float m_Speed;
    std::string m_CurrentSprite;
    float m_AnimTimer;
    unsigned char m_PlayerDirection;
    TileMap* m_pTileMap;
    bool KeyPressed;
};
