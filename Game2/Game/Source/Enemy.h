#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"

class TileMap;
class PathFinder;

class Enemy : public GameObject
{
public:
    Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, TileMap* pMap);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;
    virtual void Draw(fw::vec2 camPos, fw::vec2 projScale) override;

    
     fw::vec2 GetPosition();
    void SetPosition(fw::vec2 pos);

    unsigned char GetDirection() { return m_EnemyDirection; }

    void MoveTo(int index, float deltaTime);
    bool IsAtLocation(int index);
    void StartPathFind();

protected:

    fw::vec2 m_EnemyScale;
    float m_Speed;
    std::string m_Sprite;
    unsigned char m_EnemyDirection;
    TileMap* pTileMap;
    PathFinder* EnemyPathFinder;
    int NextTileIndex;
    bool PathFound;
    fw::vec2 EndGoal;
};
