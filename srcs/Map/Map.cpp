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
		} else if (token.find("signature") != std::string::npos)
		{
			std::getline(ss, token, '=');
			std::stringstream ss2(token);
			std::getline(ss2, token, ' ');
			int		signature = (mFormat == ExportFormat::BASIC) ? (int)token[0] : std::stoi(token);
			std::getline(ss2, token, ' ');
			mSignatures[signature] = token;
		}else if (token.find("map") != std::string::npos)
		{
			if (mFormat == ExportFormat::BASIC)
				ReadBasicFormat(mapFile);
			else
				ReadAdvancedFormat(mapFile);
			break;
		}
	}
	mapFile.close();
}

void		Map::SortElements()
{
	mElements.sort([](Element &e1, Element &e2){
		return (e1.GetGridPosition().x < e2.GetGridPosition().x);
	});
	mElements.sort([](Element &e1, Element &e2){
		return (e1.GetGridPosition().y < e2.GetGridPosition().y);
	});
}

void		Map::ReadBasicFormat(std::fstream &tFile)
{
	std::string			line;

	int y = 0;
	while (std::getline(tFile, line))
	{
		y++;
		int x = 0;
		for (auto &i : line)
		{
			x++;
			if (i == ' ')
				continue;
			Element elem(mSignatures[i]);
			elem.SetGridPosition(sf::Vector2i(x, y));
			elem.SetPosition(sf::Vector2f(x * BLOCK_SIZE, y * BLOCK_SIZE));
			mElements.push_back(elem);
		}
	}
}

void		Map::ReadAdvancedFormat(std::fstream &tFile)
{
	std::string						line;

	while (std::getline(tFile, line))
	{
		std::stringstream ss(line);
		std::string token;
		std::getline(ss, token, '=');
		if (token.find("elem") != std::string::npos)
		{
			std::getline(ss, token, '=');
			Element elem(mSignatures[std::stoi(token)]);
			mElements.push_back(elem);
		} else if (token.find("gpos") != std::string::npos)
		{
			std::getline(ss, token, '=');
			std::stringstream ss2(token);
			std::getline(ss2, token, ' ');
			int tmp = std::stoi(token);
			std::getline(ss2, token, ' ');
			mElements.back().SetGridPosition(sf::Vector2i(tmp, std::stoi(token)));
		} else if (token.find("pos") != std::string::npos)
		{
			std::getline(ss, token, '=');
			std::stringstream ss2(token);
			std::getline(ss2, token, ' ');
			float tmp = std::stof(token);
			std::getline(ss2, token, ' ');
			mElements.back().SetPosition(sf::Vector2f(tmp, std::stof(token)));
		}
	}
}



void		Map::SaveToFile()
{
	std::fstream		mapFile;

	mapFile.open(mPath, std::ios::out);
	mapFile << "name=" + mName + "\n";
	mapFile << "format=" + std::to_string((unsigned int)mFormat) + "\n";
	for (auto &i : mSignatures)
	{
		if (mFormat == ExportFormat::BASIC && i.first < 177)
			mapFile << "signature=" << (char)i.first << " " << i.second << '\n';
		else if (mFormat == ExportFormat::ADVANCED)
			mapFile << "signature=" << i.first << " " << i.second << '\n';
	}
	mapFile << '\n';
	mapFile << "map=" << '\n';
	if (mFormat == ExportFormat::BASIC)
		mapFile << GetBasicFormat();
	else
		mapFile << GetAdvancedFormat();
	mapFile.close();
}

void		Map::AddElement(Element *tElement)
{
	if (tElement)
	{
		bool exists = false;
		for (auto &i : mSignatures)
		{
			if (i.second == tElement->GetPath())
				exists = true;
		}
		int id = mSignatures.size() + 1 + 33;
		if (!exists)
			mSignatures[id] = tElement->GetPath();
		mElements.push_back(*tElement);
	}
}

void		Map::RemoveElement(sf::Vector2i tPos)
{
	mElements.remove_if([tPos](Element element){
		return (tPos == element.GetGridPosition());
	});
}

void		Map::Render(Window *tWindow)
{
	sf::Sprite	mBlockSprite;
	for (auto &i : mElements)
	{
		sf::Texture	*texture = ResourceManager::LoadTexture(i.GetPath());
		if (texture)
		{
			mBlockSprite.setTexture(*texture);
			mBlockSprite.setPosition(sf::Vector2f(i.GetGridPosition().x * BLOCK_SIZE, i.GetGridPosition().y * BLOCK_SIZE));
			mBlockSprite.setScale(sf::Vector2f(BLOCK_SIZE / texture->getSize().x, BLOCK_SIZE / texture->getSize().y));
			mBlockSprite.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
			tWindow->Draw(mBlockSprite);
		}
	}
}
