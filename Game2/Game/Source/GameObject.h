#pragma once

#include "Framework.h"
#include "DataTypes.h"

class GameObject
{
public:
    GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw();

    bool IsCollidingWith(GameObject* pOtherObject);

protected:
    fw::Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    fw::Texture* m_pTexture;

    float m_CollisionRadius;

    float m_Scale;
    vec2 m_Position;
};
