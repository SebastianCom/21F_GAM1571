#include "Framework.h"
#include "DataTypes.h"

enum  TT
{
	Empty,
	Ground,    //1
	Brick,     //2
	BoxRed,    //3
	BoxBlue,   //4
	BoxGreen,  //5
	NumTypes, //brilliant 
};

struct TileProperties
{
	fw::Mesh* m_pMesh;
	fw::ShaderProgram* m_pShader;
	fw::Texture* m_pTexture;
	bool Walkable;
	bool Moveable;
	fw::vec2 m_uvOffset;
	fw::vec2 m_uvScale;
};

class TileMap
{
public: 
	TileMap(fw::Mesh* mesh, fw::ShaderProgram* shader, fw::Texture* texture, int level);
	~TileMap();

	void SetLayout();
	void SetProperites();

	void Draw(fw::vec2 camPos, fw::vec2 projScale);
	void ReverseArrayOnY(std::vector<fw::vec2>(arraytoreverse));

	fw::vec2 GetUVScale(unsigned char pTiles);
	fw::vec2 GetUVOffset(unsigned char pTiles);

private:


	int m_Height; 
	int m_Width; 
	const int MaxTiles = 100;
	unsigned char* pTiles; 
	std::vector<fw::vec2> m_2DLayout;
	std::vector<fw::vec2> m_WorldLayout;
	fw::vec2 m_Scale;
	fw::SpriteSheet* m_pSpriteSheet;
	fw::Mesh* m_pMesh;
	fw::ShaderProgram* m_pShader;
	fw::Texture* m_pTexture;
	TileProperties* m_pTileProperties;
	int m_ElevationLevel;
	fw::vec2 m_ReversedWorldLayout[100];

	
};

