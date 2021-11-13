#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 pos)
    : m_pMesh( pMesh )
    , m_pShader( pShader )
    , m_Scale( 1.0f )
    , m_Position( pos )
{
    m_CollisionRadius = 5.0f;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(vec2 camPos, vec2 projScale)//camPos, projScale,
{
    m_pMesh->Draw( m_pShader, m_Scale, m_Position, 0.0f, camPos, projScale );
}

bool GameObject::IsCollidingWith(GameObject* pOtherObject)
{
    float combinedRadii = m_CollisionRadius + pOtherObject->m_CollisionRadius;
    float dist = m_Position.DistanceTo( pOtherObject->m_Position );
    
    if( dist < combinedRadii )
        return true;

    return false;
}
