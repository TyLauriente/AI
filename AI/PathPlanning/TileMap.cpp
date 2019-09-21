#include "TileMap.h"



TileMap::TileMap()
{
}


TileMap::~TileMap()
{
	delete[] m_textureIDs;
	delete m_map;
}

void TileMap::XInitialize()
{
	//Load Textures
	TileMapFileParser parser;
	m_textureCount = parser.GetAmountTextures();

	m_textureIDs = parser.GetTextureIDs();

	m_tileWidth = static_cast<float>(X::GetSpriteWidth(m_textureIDs[0]));
	m_tileHeight = static_cast<float>(X::GetSpriteHeight(m_textureIDs[0]));
	//Load Map
	m_map = parser.GetMap();
	//Set Scrren dimensions
	m_screenWidth = static_cast<float>(X::GetScreenWidth());
	m_screenHeight = static_cast<float>(X::GetScreenHeight());
}


void TileMap::Render()
{
	X::Math::Vector2 drawPos{ 0.0f, 0.0f };
	for (int row = 0; row < m_map->GetRows(); ++row)
	{
		for (int column = 0; column < m_map->GetColumns(); ++column)
		{
			int pos = m_map->ConvertToPos(row, column);
			X::DrawSprite(m_textureIDs[m_map->Get(pos)], ConvertForRender(drawPos));
			drawPos.x += m_tileWidth;
		}
		drawPos.x = 0.0f;
		drawPos.y += m_tileHeight;
	}
}

bool TileMap::CheckCollision(const X::Math::LineSegment& edge) const
{
	const auto startX = static_cast<int>(edge.from.x / m_tileWidth);
	const auto startY = static_cast<int>(edge.from.y / m_tileHeight);
	const auto endX = static_cast<int>(edge.to.x / m_tileWidth);
	const auto endY = static_cast<int>(edge.to.y / m_tileHeight);

	for (int y = startY; y <= endY; ++y)
	{
		for (int x = startX; x <= endX; ++x)
		{
			if (m_map->Get(y, x) > 1)
				return true;
		}
	}
	return false;
}

void TileMap::ChangeMap(int row, int collumn, int block)
{
	if(row < m_map->GetRows() && collumn < m_map->GetColumns() && block < m_textureCount)
	{
		m_map->Set(row, collumn, block);
	}
}