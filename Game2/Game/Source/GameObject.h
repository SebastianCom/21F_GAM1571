#pragma once

#include "Framework.h"
#include "DataTypes.h"

class SpriteInfo;

class GameObject
{
public:
    GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, char sheetNumber);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw(fw::vec2 camPos, fw::vec2 projScale);

    bool IsCollidingWith(GameObject* pOtherObject);

    void HardCodeNames();



protected:
    fw::Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    fw::Texture* m_pTexture;

    float m_CollisionRadius;

    vec2 m_Scale;
    vec2 m_Position;
    
    fw::SpriteSheet* m_pSpriteSheet;
    std::map<std::string, std::string> m_Sprites;
};
