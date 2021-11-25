#include "Framework.h"
#include "TileMap.h"

TileMap::TileMap()
{
	 m_Height = 10;
	 m_Width = 10;
	 pTiles = new unsigned char [m_Height * m_Width];
	 SetLayout();
	 m_2DLayout;
	 m_WorldLayout;
	 m_Scale = 5;



	 for (int i = 0; i < 100; i++)
	 {
		 int x = i % m_Width;
		 int y = i / m_Width;

		 m_2DLayout.push_back(fw::vec2(x,y));
	 }
	 for (int i = 0; i < 100; i++)
	 {
		 int x = m_2DLayout[i].x * m_Scale;
		 int y = m_2DLayout[i].y * m_Scale;

		 m_WorldLayout.push_back(fw::vec2(x, y));
	 }
	 

	 TileProperties* m_pTileProperties = new TileProperties[TT::NumTypes];


}

TileMap::~TileMap()
{
}

void TileMap::SetLayout()
{
	unsigned char pLayout[100] =
	{
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
		Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick, Brick,
	};

	for (int i = 0; i < 100; i++)
	{
		pTiles[i] = pLayout[i];
	}
}





