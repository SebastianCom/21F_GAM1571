#include "Framework.h"
#include "TileMap.h"

TileMap::TileMap(fw::Mesh* mesh, fw::ShaderProgram* shader, fw::Texture* texture, int level) :
	m_pMesh(mesh),
	m_pShader(shader),
	m_pTexture(texture),
	m_ElevationLevel(level)
{
	//init list
	 m_Height = 10;
	 m_Width = 10;
	 pTiles = new unsigned char [long long(m_Height) * m_Width]; //need 8 bytes and it would not allow me to cast to a pointed
	 pReversedTiles = new unsigned char [long long(m_Height) * m_Width]; //need 8 bytes and it would not allow me to cast to a pointed
	 SetLayout();
	 m_WorldLayout;
	 m_Scale = fw::vec2(5,5);
	 m_pSpriteSheet = new fw::SpriteSheet(1);
	 m_TileSizeX = int(m_Scale.x) * m_Height;
	 m_TileSizeY = int(m_Scale.y) * m_Height;


	 for (int i = 0; i < MaxTiles; i++) 
	 {
		 float x = i % m_Width * (m_TileSizeX);
		 float y = i / m_Width * (m_TileSizeY);
		 m_WorldLayout.push_back(fw::vec2(x, y)); 
	 }

	 m_pTileProperties = new TileProperties[TT::NumTypes];
	 SetProperites();
}

TileMap::~TileMap()
{
	delete pTiles;
	delete pReversedTiles;
	delete m_pSpriteSheet;
	delete m_pTileProperties;
}



void TileMap::Draw(fw::vec2 camPos, fw::vec2 projScale)
{
	int sheetWidth = m_pSpriteSheet->GetSheetWidth();
	for (int i = 0; i < MaxTiles; i++)
	{	
		m_pMesh->Draw(m_pShader, m_pTexture, m_Scale, m_WorldLayout[i], 0.0f, camPos, projScale, GetUVScale(pTiles[i]), GetUVOffset(pTiles[i]));
	}
	
	//Reminder Coder
	//m_pMesh->Draw(Shader, Texture, 2DlayoutAtI, worldPosAtI, 0.0f, camPos, projScale, sheetWidth, uvScale, uvOffset);
}


//------------------------------My Functions-----------------------------------------------------

bool TileMap::IsWalkableAtLocation(int x, int y)
{

	int index = y * m_pSpriteSheet->GetSheetWidth() + x;

	if (m_pTileProperties[index].Walkable == true)
	{
		return false;
	}
	else
	return true;
}

unsigned char TileMap::GetTile(int index)
{
	return pTiles[index];
}

TileProperties TileMap::GetTileProperties(char tile)
{
	return m_pTileProperties[tile];
}

void TileMap::SwapTiles(char tile, char newtile)
{
	unsigned char temp = pTiles[tile];
	pTiles[tile] = pTiles[newtile];
	pTiles[newtile] = temp;
}




void TileMap::SetLayout()
{
	unsigned char pGroundLayout[100] =
	{
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
		Ground, Ground, Ground, Ground, Ground, Ground, Ground,Ground, Ground, Ground,
	};	
	unsigned char pLayout[100] =
	{
		Brick, Brick, Brick,   Brick, Brick, Brick, Brick,    Brick, Brick, Brick,
		Brick, Empty, BoxRed,  Empty, Empty, Brick, Empty,    Empty, Empty, Brick,
		Brick, Empty, Empty,   Empty, Empty, Brick, Empty,    Empty, Empty, Brick,
		Brick, Empty, Empty,   Empty, Empty, Empty, Empty,    Empty, Empty, Brick,
		Brick, Empty, Empty,   Empty, Empty, Empty, Empty,    Empty, Brick, Brick,
		Brick, Empty, Empty,   Empty, Empty, Empty, BoxGreen, Empty, Empty, Brick, //pushed after here
		Brick, Empty, Empty,   Empty, Empty, Empty, Empty,    Empty, Empty, Brick,
		Brick, Empty, BoxBlue, Brick, Empty, Empty, Empty,    Empty, Empty, Brick,
		Brick, Empty, Empty,   Brick, Empty, Empty, Empty,    Empty, Empty, Brick,
		Brick, Brick, Brick,   Brick, Brick, Brick, Brick,    Brick, Brick, Brick,
	};

	if (m_ElevationLevel == 1)
	{
		for (int i = 0; i < 100; i++)
		{
			pTiles[i] = pGroundLayout[i];
		}
	}
	else if (m_ElevationLevel == 2)
	{
		for (int i = 0; i < 100; i++)
		{
			pTiles[i] = pLayout[i];
		}
	}
	for (int i = 0; i < 100; i++)
	{
		int temp = pTiles[i];
		pTiles[i] = pTiles[(100 - i) - 1];
		pTiles[100 - i] = temp;
	}
}

void TileMap::SetProperites()
{
	m_pTileProperties[TT::Empty].Moveable = false;
	m_pTileProperties[TT::Empty].Walkable = true;
	m_pTileProperties[TT::Empty].m_pShader = nullptr;
	m_pTileProperties[TT::Empty].m_pTexture = nullptr;
	m_pTileProperties[TT::Empty].m_pMesh = nullptr;
	m_pTileProperties[TT::Empty].m_uvScale = fw::vec2(0,0);
	m_pTileProperties[TT::Empty].m_uvOffset = fw::vec2(0, 0);

	m_pTileProperties[TT::Ground].Moveable = false;
	m_pTileProperties[TT::Ground].Walkable = true;
	m_pTileProperties[TT::Ground].m_pShader = m_pShader;
	m_pTileProperties[TT::Ground].m_pTexture = m_pTexture;
	m_pTileProperties[TT::Ground].m_pMesh = m_pMesh;
	m_pTileProperties[TT::Ground].m_uvScale = m_pSpriteSheet->GetSpriteInfo("ground_06").UVScale;
	m_pTileProperties[TT::Ground].m_uvOffset = m_pSpriteSheet->GetSpriteInfo("ground_06").UVOffset;

	m_pTileProperties[TT::Brick].Moveable = false;
	m_pTileProperties[TT::Brick].Walkable = false;
	m_pTileProperties[TT::Brick].m_pShader = m_pShader;
	m_pTileProperties[TT::Brick].m_pTexture = m_pTexture;
	m_pTileProperties[TT::Brick].m_pMesh = m_pMesh;
	m_pTileProperties[TT::Brick].m_uvScale = m_pSpriteSheet->GetSpriteInfo("block_01").UVScale;
	m_pTileProperties[TT::Brick].m_uvOffset = m_pSpriteSheet->GetSpriteInfo("block_01").UVOffset;

	m_pTileProperties[TT::BoxRed].Moveable = true;
	m_pTileProperties[TT::BoxRed].Walkable = false;
	m_pTileProperties[TT::BoxRed].m_pShader = m_pShader;
	m_pTileProperties[TT::BoxRed].m_pTexture = m_pTexture;
	m_pTileProperties[TT::BoxRed].m_pMesh = m_pMesh;
	m_pTileProperties[TT::BoxRed].m_uvScale = m_pSpriteSheet->GetSpriteInfo("crate_03").UVScale;
	m_pTileProperties[TT::BoxRed].m_uvOffset = m_pSpriteSheet->GetSpriteInfo("crate_03").UVOffset;

	m_pTileProperties[TT::BoxBlue].Moveable = true;
	m_pTileProperties[TT::BoxBlue].Walkable = false;
	m_pTileProperties[TT::BoxBlue].m_pShader = m_pShader;
	m_pTileProperties[TT::BoxBlue].m_pTexture = m_pTexture;
	m_pTileProperties[TT::BoxBlue].m_pMesh = m_pMesh;
	m_pTileProperties[TT::BoxBlue].m_uvScale = m_pSpriteSheet->GetSpriteInfo("crate_04").UVScale;
	m_pTileProperties[TT::BoxBlue].m_uvOffset = m_pSpriteSheet->GetSpriteInfo("crate_04").UVOffset;

	m_pTileProperties[TT::BoxGreen].Moveable = true;
	m_pTileProperties[TT::BoxGreen].Walkable = false;
	m_pTileProperties[TT::BoxGreen].m_pShader = m_pShader;
	m_pTileProperties[TT::BoxGreen].m_pTexture = m_pTexture;
	m_pTileProperties[TT::BoxGreen].m_pMesh = m_pMesh;
	m_pTileProperties[TT::BoxGreen].m_uvScale = m_pSpriteSheet->GetSpriteInfo("crate_05").UVScale;
	m_pTileProperties[TT::BoxGreen].m_uvOffset = m_pSpriteSheet->GetSpriteInfo("crate_05").UVOffset;


}


fw::vec2 TileMap::GetUVScale(unsigned char Tiles)
{
	fw::vec2 uvScale = fw::vec2(0, 0);

	uvScale = m_pTileProperties[Tiles].m_uvScale;

	return uvScale;
}

fw::vec2 TileMap::GetUVOffset(unsigned char Tiles)
{

	fw::vec2 uvOffset = fw::vec2(0, 0);

	uvOffset = m_pTileProperties[Tiles].m_uvOffset;

	return uvOffset;
}






