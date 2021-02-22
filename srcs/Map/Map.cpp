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


std::string	Map::GetBasicFormat()
{
	std::string result = "";
	if (mElements.size() < 1)
		return "";
	mElements.sort([](Element &e1, Element &e2){
		return (e1.GetGridPosition().x < e2.GetGridPosition().x);
	});
	mElements.sort([](Element &e1, Element &e2){
		return (e1.GetGridPosition().y < e2.GetGridPosition().y);
	});
	sf::Vector2i	max = mElements.front().GetGridPosition(), min = mElements.front().GetGridPosition();
	for (auto &i : mElements)
	{
		sf::Vector2i	pos = i.GetGridPosition();
		if (pos.x < min.x)
			min.x = pos.x;
		if (pos.y < min.y)
			min.y = pos.y;
		if (pos.x > max.x)
			max.x = pos.x;
		if (pos.y > max.y)
			max.y = pos.y;
	}
	std::list<Element>::iterator it = mElements.begin();
	for (int i = min.y; i <= max.y; i++)
	{
		for (int j = min.x; j <= max.x; j++)
		{
			if (it->GetGridPosition().x > j || it->GetGridPosition().y > i )
				result += ' ';
			else
			{
				int signature = (int)(' ');
				for (auto &k : mSignatures)
				{
					if (k.second == it->GetPath())
						signature = k.first;
				}
				result += (char)signature;
				it++;
			}
		}
		result += '\n';
	}
	return (result);
}

std::string	Map::GetAdvancedFormat()
{
	return ("");
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
