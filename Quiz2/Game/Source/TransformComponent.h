#pragma once

#include "Framework.h"
#include "DataTypes.h"

#include "Component.h"

class Component;

class TransformComponent : public Component
{
public:
    TransformComponent(vec2 scale, vec2 pos);
    virtual ~TransformComponent();

    vec2 m_Scale;
    vec2 m_Position;

protected:

};

TransformComponent::TransformComponent(vec2 scale, vec2 pos)
{
    m_Scale = scale;
    m_Position = pos;
}

inline TransformComponent::~TransformComponent()
{
}

