#pragma once

#include "Framework.h"
#include "DataTypes.h"


class Game;
class Component;


class GameObject
{
public:
    GameObject(Game* pGame, fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 scale, vec2 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw(vec2 projScale, vec2 camPos);

    int CheckComponent(Component* comp);

protected:

    std::vector<Component*> m_pComponents;

    //// Rendering data.
    //fw::Mesh* m_pMesh;
    //fw::ShaderProgram* m_pShader;

    //// Transform data.
    //vec2 m_Scale;
    //vec2 m_Position;
};
