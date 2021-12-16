#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"
#include <random>
#include <iostream>

class TileMap;
class PathFinder;
class Player;


class Enemy : public GameObject
{
public:
    Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, TileMap* pMap, Player* pPlayer, int type);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;
    virtual void Draw(fw::vec2 camPos, fw::vec2 projScale) override;

    
     fw::vec2 GetPosition();
    void SetPosition(fw::vec2 pos);

    unsigned char GetDirection() { return m_EnemyDirection; }

    void MoveTo(int index, float deltaTime);
    bool IsAtLocation(int index);
    void StartPathFind();

    typedef void (Enemy::* AIStateFunction)(float deltaTime);
    //Ai States attempt1 - it worked lol
    void AIState_Idle(float deltaTime);
    void AIState_Searching(float deltaTime);
    void AIState_Chasing(float deltaTime);
    void RandomizeEndGoal();

    void ResetState();

    void DisplayState(const char* state);

protected:

    fw::vec2 m_EnemyScale;
    fw::vec2 m_LastLocation;
    float m_Speed;
    std::string m_Sprite;
    unsigned char m_EnemyDirection;
    TileMap* pTileMap;
    PathFinder* EnemyPathFinder;
    int NextTileIndex;
    bool PathFound;
    fw::vec2 EndGoal;

    Player* m_pPlayer;

    AIStateFunction m_CurrentAIState;
    float IdleTimer;
    bool Atlocation;
    const char* CurrentStateName;
};
