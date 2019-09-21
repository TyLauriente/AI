#include "TileMapFileParser.h"



TileMapFileParser::TileMapFileParser()
{
	m_textures = GetAmountTextures();
}


TileMapFileParser::~TileMapFileParser()
= default;

int TileMapFileParser::GetAmountTextures() const
{
	std::ifstream file(std::ifstream(TEXTURES_FILE, std::ios::in));
	//Determine amount of textures in file
	std::string input;
	while(input != " ")
	{
		input = static_cast<char>(file.get());
	}
	std::getline(file, input);
	return std::stoi(input);
}

X::TextureId* TileMapFileParser::GetTextureIDs() const
{
	//Place textures into array and return
	if (m_textures > 0)
	{
		std::ifstream file(TEXTURES_FILE, std::ios::in);
		const auto result = new X::TextureId[m_textures];
		std::string texture;
		std::getline(file, texture);
		for (int textures = 0; textures < m_textures; ++textures)
		{
			std::getline(file, texture);
			result[textures] = X::LoadTexture(texture.c_str());
		}
		file.close();
		return result;
	}
	else
	{
		return nullptr;
	}
}



Dynamic2DArray<int>* TileMapFileParser::GetMap() const
{
	std::ifstream file(MAP_FILE, std::ios::in);
	std::string line;

	//Determine amount of rows
	std::getline(file, line);
	line = "";
	while (line != " ")
	{
		line = static_cast<char>(file.get());
	}
	std::getline(file, line);
	const int rows = std::stoi(line);
	//Determine amount of columns
	line = "";
	while (line != " ")
	{
		line = static_cast<char>(file.get());
	}
	std::getline(file, line);
	const int columns = std::stoi(line);

	if (rows == 0 && columns == 0)
	{
		return nullptr;
	}
	//Place the map values from file into an array and return
	auto map = new Dynamic2DArray<int>(rows, columns);
	for (int index = 0; index < rows*columns; ++index)
	{
		line = static_cast<char>(file.get());
		if (line != "\n" && line != "ÿ")
		{
			const int value = std::stoi(line);
			map->Set(index, value);
		}
		else
		{
			index--;
		}
	}
	file.close();
	return map;
}
