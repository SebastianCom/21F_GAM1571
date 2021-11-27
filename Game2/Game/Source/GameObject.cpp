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

}

bool GameObject::IsCollidingWith(GameObject* pOtherObject)
{
    float combinedRadii = m_CollisionRadius + pOtherObject->m_CollisionRadius;
    float dist = m_Position.DistanceTo( pOtherObject->m_Position );
    
    if( dist < combinedRadii )
        return true;

    return false;
}

//I did this more for fun to see if i could create a map, i really couldve just set string variables for all of them
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
    m_Sprites["Player Down2"] = "player_06";
    m_Sprites["Player Down3"] = "player_07";
   
    m_Sprites["Player Up"] = "player_08";
    m_Sprites["Player Up2"] = "player_09";
    m_Sprites["Player Up3"] = "player_10";
    
    m_Sprites["Player Left"] = "player_20";
    m_Sprites["Player Left2"] = "player_21";
    m_Sprites["Player Left3"] = "player_22";
   
    m_Sprites["Player Right"] = "player_17";
    m_Sprites["Player Right2"] = "player_18";
    m_Sprites["Player Right3"] = "player_19";

}
