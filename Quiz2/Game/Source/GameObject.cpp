#include "Framework.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"

GameObject::GameObject(Game* pGame, fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 scale, vec2 pos)
{
    m_pComponents.push_back(new TransformComponent(scale, pos));
    m_pComponents.push_back(new RenderComponent(pMesh, pShader));
}

GameObject::~GameObject()
{
    for (int i = 0; i < m_pComponents.size(); i++)
    {
        delete m_pComponents[i];
    }
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(vec2 projScale, vec2 camPos)
{
    RenderComponent* Rend = nullptr;
    TransformComponent* Tran = nullptr;
    for (int i = 0; i < m_pComponents.size(); i++)
    {
        int CompNum = CheckComponent(m_pComponents[i]);
        if (CompNum == 1)
        {
             Tran = dynamic_cast<TransformComponent*>(m_pComponents[i]);
             Rend = dynamic_cast<RenderComponent*>(m_pComponents[!i]);
        }
        else
        {
            Rend = dynamic_cast<RenderComponent*>(m_pComponents[i]);
            Tran = dynamic_cast<TransformComponent*>(m_pComponents[!i]); 
        }
    }
    
    if(Rend && Tran)
    Rend->m_pMesh->Draw(Rend->m_pShader, nullptr, projScale, camPos, Tran->m_Scale, Tran->m_Position, vec2(1, 1), vec2(0, 0), 0.0f);
    
}

int GameObject::CheckComponent(Component* comp)
{
    TransformComponent* temp = dynamic_cast<TransformComponent*>(comp);
    if(temp != nullptr)
    return 1;
    else
    {
        RenderComponent* temp = dynamic_cast<RenderComponent*>(comp);
        if (temp != nullptr)
            return 2;
        else
            return 3; // finally remebered to make sure every case returns something
    }

}
