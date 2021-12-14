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
	fw::Mesh* m_pMesh = nullptr;
	fw::ShaderProgram* m_pShader = nullptr;
	fw::Texture* m_pTexture = nullptr;
	bool Walkable = false;
	bool Moveable = false;
	fw::vec2 m_uvOffset = fw::vec2(0,0);
	fw::vec2 m_uvScale = fw::vec2(0, 0);
};

class TileMap
{
public: 
	TileMap(fw::Mesh* mesh, fw::ShaderProgram* shader, fw::Texture* texture, int level);
	~TileMap();

	void SetLayout();
	void SetProperites();

	void Draw(fw::vec2 camPos, fw::vec2 projScale);

	fw::vec2 GetUVScale(unsigned char Tiles);
	fw::vec2 GetUVOffset(unsigned char Tiles);

	int GetTileSize() { return m_TileSizeX; }
	int GetTileMapWidth() { return m_Width; }
	int GetTileMapHeight() { return m_Height; }

	bool IsWalkableAtLocation(int x, int y);

	unsigned char GetTile(int index);
	TileProperties GetTileProperties(char tile);

	void SwapTiles(char tile, char newtile);

private:


	int m_Height; 
	int m_Width; 
	const int MaxTiles = 100;
	unsigned char* pTiles; 
	unsigned char* pReversedTiles; 
	std::vector<fw::vec2> m_WorldLayout;
	fw::vec2 m_Scale;
	fw::SpriteSheet* m_pSpriteSheet;
	fw::Mesh* m_pMesh;
	fw::ShaderProgram* m_pShader;
	fw::Texture* m_pTexture;
	TileProperties* m_pTileProperties;
	int m_ElevationLevel;
	int m_TileSizeX;
	int m_TileSizeY;

	
};

