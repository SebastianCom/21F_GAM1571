#include "Framework.h"
#include "TileMap.h"

TileMap::TileMap(fw::Mesh* mesh, fw::ShaderProgram* shader, fw::Texture* texture, int level) :
	m_pMesh(mesh),
	m_pShader(shader),
	m_pTexture(texture),
	m_ElevationLevel(level)
{
	 m_Height = 10;
	 m_Width = 10;
	 pTiles = new unsigned char [m_Height * m_Width];
	 SetLayout();
	 m_2DLayout;
	 m_WorldLayout;
	 m_Scale = fw::vec2(5,5);
	 m_pSpriteSheet = new fw::SpriteSheet();



	 for (int i = 0; i < MaxTiles; i++)
	 {
		 int x = i % m_Width;
		 int y = i / m_Width;

		 m_2DLayout.push_back(fw::vec2(x,y));
	 }
	 for (int i = 0; i < MaxTiles; i++)
	 {
		 int x = m_2DLayout[i].x * (m_Scale.x * m_Width);
		 int y = m_2DLayout[i].y * (m_Scale.y * m_Height);
		 m_WorldLayout.push_back(fw::vec2(x, y));
	 }
	 
	 m_pTileProperties = new TileProperties[TT::NumTypes];
	 SetProperites();

}

TileMap::~TileMap()
{
}



void TileMap::Draw(fw::vec2 camPos, fw::vec2 projScale)
{
	float sheetWidth = m_pSpriteSheet->GetSheetWidth();
	for (int i = 0; i < MaxTiles; i++)
	{	
		ReverseArrayOnY(m_WorldLayout);
		m_pMesh->Draw(m_pShader, m_pTexture, m_Scale, m_ReversedWorldLayout[i], 0.0f, camPos, projScale, sheetWidth, GetUVScale(pTiles[i]), GetUVOffset(pTiles[i]));
	}
	
	//m_pMesh->Draw(m_pShader, m_pTexture, 2DlayoutAtI, worldPosAtI, 0.0f, camPos, projScale, sheetWidth, uvScale, uvOffset);
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
		Brick, Brick, Brick, Brick, Brick, Brick, Brick,Brick, Brick, Brick,
		Brick, Empty, Empty, Empty, Empty, Empty, Empty,Empty, Empty, Brick,
		Brick, Empty, Empty, Empty, Empty, Empty, Empty,Empty, Empty, Brick,
		Brick, Empty, Empty, Empty, Empty, Empty, Empty,Empty, Empty, Brick,
		Brick, Empty, Empty, Empty, Empty, Empty, Empty,Empty, Empty, Brick,
		Brick, Empty, Empty, Empty, Empty, Empty, Empty,Empty, Empty, Brick,
		Brick, Empty, Empty, Empty, Empty, Empty, Empty,Empty, Empty, Brick,
		Brick, Empty, Empty, Empty, Empty, Empty, Empty,Empty, Empty, Brick,
		Brick, Empty, Empty, Empty, Empty, Empty, Empty,Empty, Empty, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick,Brick, Brick, Brick,
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

	m_pTileProperties[TT::Ground].Moveable = false;
	m_pTileProperties[TT::Ground].Walkable = false;
	m_pTileProperties[TT::Ground].m_pShader = m_pShader;
	m_pTileProperties[TT::Ground].m_pTexture = m_pTexture;
	m_pTileProperties[TT::Ground].m_pMesh = m_pMesh;
	m_pTileProperties[TT::Ground].m_uvScale = m_pSpriteSheet->GetSpriteInfo("ground_06").UVScale;
	m_pTileProperties[TT::Ground].m_uvOffset = m_pSpriteSheet->GetSpriteInfo("ground_06").UVOffset;
}

void TileMap::ReverseArrayOnY(std::vector<fw::vec2>(arraytoreverse))
{
	int num = 100;

	for (int i = 0; i < num; i++)
	{
		m_ReversedWorldLayout[i].x = arraytoreverse[i].x;
		int otherIndex = (num - 1) - i;
		m_ReversedWorldLayout[i].y = arraytoreverse[otherIndex].y;
	}
}

fw::vec2 TileMap::GetUVScale(unsigned char pTiles)
{
	fw::vec2 uvScale = fw::vec2(0, 0);

	if (pTiles == Brick)
	{
		uvScale = m_pTileProperties[Brick].m_uvScale;
	}
	else if (pTiles == BoxRed)
	{
		uvScale = m_pTileProperties[BoxRed].m_uvScale;
	}
	else if (pTiles == BoxBlue)
	{
		uvScale = m_pTileProperties[BoxBlue].m_uvScale;
	}
	else if (pTiles == BoxGreen)
	{
		uvScale = m_pTileProperties[BoxGreen].m_uvScale;
	}
	else if (pTiles == Ground)
	{
		uvScale = m_pTileProperties[Ground].m_uvScale;
	}
	else if (pTiles == Empty)
	{
		uvScale = m_pTileProperties[Empty].m_uvScale;
	}
	return uvScale;
}

fw::vec2 TileMap::GetUVOffset(unsigned char pTiles)
{

	fw::vec2 uvOffset = fw::vec2(0, 0);

	if (pTiles == Brick)
	{
		uvOffset = m_pTileProperties[Brick].m_uvOffset;
	}
	else if (pTiles == BoxRed)
	{
		uvOffset = m_pTileProperties[BoxRed].m_uvOffset;
	}
	else if (pTiles == BoxBlue)
	{
		uvOffset = m_pTileProperties[BoxBlue].m_uvOffset;
	}
	else if (pTiles == BoxGreen)
	{
		uvOffset = m_pTileProperties[BoxGreen].m_uvOffset;
	}
	else if (pTiles == Ground)
	{
		uvOffset = m_pTileProperties[Ground].m_uvOffset;
	}
	else if (pTiles == Empty)
	{
		uvOffset = m_pTileProperties[Empty].m_uvOffset;
	}
	return uvOffset;
}






