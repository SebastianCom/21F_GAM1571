#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Component.h"

class Component;

class RenderComponent : public Component
{
public:
    RenderComponent(fw::Mesh* mesh, fw::ShaderProgram* shader);
    virtual ~RenderComponent();

    // Rendering data.
    fw::Mesh* m_pMesh = nullptr;
    fw::ShaderProgram* m_pShader = nullptr;
   
};

RenderComponent::RenderComponent(fw::Mesh* mesh, fw::ShaderProgram* shader)
{
    m_pMesh = mesh;
    m_pShader = shader;
}

inline RenderComponent::~RenderComponent()
{
}
