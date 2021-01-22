#include "Map.hpp"

Map::Map(std::string tPath)
{
	mPath = tPath;
	Load();
}

Map::Map(/* args */)
{
}

Map::~Map()
{
}

void	Map::Load()
{
	std::fstream		mapFile;
	std::string			line;

	mapFile.open(mPath, std::ios::in);
	while (std::getline(mapFile, line))
	{
		std::stringstream ss(line);
		std::string token;
		std::getline(ss, token, '=');
		if (token.find("name") != std::string::npos)
		{
			std::getline(ss, token, '=');
			mName = token;
		} else if (token.find("format") != std::string::npos)
		{
			std::getline(ss, token, '=');
			mFormat = (ExportFormat)std::stoi(token);
		}
	}
}
