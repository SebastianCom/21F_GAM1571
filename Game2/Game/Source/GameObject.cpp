#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos)
    : m_pMesh( pMesh )
    , m_pShader( pShader )
    , m_pTexture( pTexture )
    , m_Scale( 1,1 )
    , m_Position( pos )
{
   
    m_CollisionRadius = 5.0f;
    HardCodeNames();
    m_pSpriteSheet = new fw::SpriteSheet();
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
    
}

void GameObject::Draw(fw::vec2 camPos, fw::vec2 projScale) //TODO projScale, camPos
{
    float sheetWidth = m_pSpriteSheet->GetSheetWidth();
    fw::vec2 uvOffset = m_pSpriteSheet->GetSpriteInfo(m_Sprites["Red Box"]).UVOffset;
    fw::vec2 uvScale = m_pSpriteSheet->GetSpriteInfo(m_Sprites["Red Box"]).UVScale;
    m_pMesh->Draw( m_pShader, m_pTexture, m_Scale, m_Position, 0.0f, camPos, projScale, sheetWidth, uvScale, uvOffset);
}

bool GameObject::IsCollidingWith(GameObject* pOtherObject)
{
    float combinedRadii = m_CollisionRadius + pOtherObject->m_CollisionRadius;
    float dist = m_Position.DistanceTo( pOtherObject->m_Position );
    
    if( dist < combinedRadii )
        return true;

    return false;
}

void GameObject::HardCodeNames()
{
    m_Sprites["Red Brick"] = "block_01";
    m_Sprites["Brown Brick"] = "block_03";
    m_Sprites["Grey Brick"] = "block_02";
    
    m_Sprites["Brown Box"] = "crate_02";
    m_Sprites["Red Box"] = "crate_03";
    m_Sprites["Blue Box"] = "crate_04";
    m_Sprites["Green Box"] = "crate_05";
    m_Sprites["Grey Box"] = "crate_06";
    
    m_Sprites["Dirt"] = "ground_01";
    m_Sprites["Grass"] = "ground_05";
    m_Sprites["Stone"] = "ground_06";
    
    m_Sprites["Player Down"] = "player_05";
    m_Sprites["Player Up"] = "player_08";
    m_Sprites["Player Left"] = "player_20";
    m_Sprites["Player Right"] = "player_17";

}
