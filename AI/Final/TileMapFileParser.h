#ifndef TILEMAPFILEPARSER_INCLUDED_HEADER
#define TILEMAPFILEPARSER_INCLUDED_HEADER

#include<iostream>
#include <fstream>
#include<XEngine.h>
#include"Dynamic2DArray.h"

class TileMapFileParser
{
public:
	TileMapFileParser();
	~TileMapFileParser();

	int GetAmountTextures() const;

	X::TextureId* GetTextureIDs() const;

	Dynamic2DArray<int>* GetMap() const;
	

private:
	const std::string MAP_FILE = "Map.txt";
	const std::string TEXTURES_FILE = "Textures.txt";
	int m_textures;
};

#endif