#include "Framework.h"
#include "DataTypes.h"

enum  TT
{
	Ground,    //0
	Brick,     //1
	BoxRed,    //2
	BoxBlue,   //3
	BoxGreen,  //4
	NumTypes, //brilliant 
};

struct TileProperties
{
	fw::Mesh* m_pMesh;
	fw::ShaderProgram* m_pShader;
	fw::Texture* m_pTexture;
	bool Walkable;
	bool Moveable;
};

class TileMap
{
public: 
	TileMap();
	~TileMap();

	void SetLayout();

private:

	int m_Height; 
	int m_Width; 
	unsigned char* pTiles; 
	std::vector<fw::vec2> m_2DLayout;
	std::vector<fw::vec2> m_WorldLayout;
	int m_Scale;
	
};

