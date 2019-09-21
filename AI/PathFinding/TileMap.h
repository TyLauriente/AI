#ifndef TILEMAP_INCLUDED_HEADER
#define TILEMAP_INCLUDED_HEADER

#include"Dynamic2DArray.h"
#include<XEngine.h>
#include"TileMapFileParser.h"
#include"CameraManager.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	void XInitialize();

	void Render() const;

	bool CheckCollision(const X::Math::LineSegment& edge) const;

	void ChangeMap(int row, int collumn, int block);

	int GetRows() const { return m_map->GetRows(); }

	int GetColumns() const { return m_map->GetColumns(); }

	float GetTile(int row, int column) { return static_cast<float>(m_map->Get(row, column)); }

	float GetTileSize() { return m_tileWidth; }

private:
	int m_textureCount;
	float m_tileWidth;
	float m_tileHeight;
	Dynamic2DArray<int>* m_map;
	X::TextureId* m_textureIDs;
	float m_screenWidth;
	float m_screenHeight;
};

#endif