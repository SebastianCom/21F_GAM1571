#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"



class Enemy : public GameObject
{
public:
    Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;
    virtual void Draw(fw::vec2 camPos, fw::vec2 projScale) override;

    
     fw::vec2 GetPosition();
    void SetPosition(fw::vec2 pos);

    unsigned char GetDirection() { return m_EnemyDirection; }

protected:

    fw::vec2 m_EnemyScale;
    float m_Speed;
    std::string m_Sprite;
    unsigned char m_EnemyDirection;
};
