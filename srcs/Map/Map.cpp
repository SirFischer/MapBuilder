#include "Map.hpp"

sf::Texture* TryLoadTexture(const std::string& texturePath, const std::string& mapPath = "", const std::string& profileAssetsPath = "") {
	sf::Texture* texture = nullptr;
	
	std::filesystem::path textureFile(texturePath);
	std::string fileName = textureFile.filename().string();
	
	// 1. Try defaultResources first
	std::string defaultPath = "assets/defaultResources/" + fileName;
	texture = ResourceManager::LoadTexture(defaultPath);
	if (texture) return texture;
	
	// 2. Try profile assets
	if (!profileAssetsPath.empty()) {
		std::string profilePath = profileAssetsPath + "/" + fileName;
		texture = ResourceManager::LoadTexture(profilePath);
		if (texture) return texture;
	}
	
	// 3. Try map's textures folder
	if (!mapPath.empty()) {
		std::filesystem::path mapPathObj(mapPath);
		std::string mapBaseName = mapPathObj.stem().string();
		std::string mapTexturesPath = "assets/maps/" + mapBaseName + "/textures/" + fileName;
		texture = ResourceManager::LoadTexture(mapTexturesPath);
		if (texture) return texture;
	}
	
	return nullptr;
}

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

void		Map::NormalizeElements()
{
	int x = 0;
	int y = 0;
	for (auto &i : mElements)
	{
		if (i.GetGridPosition().x < x)
			x = i.GetGridPosition().x;
		if (i.GetGridPosition().y < y)
			y = i.GetGridPosition().y;
	}
	for (auto &i : mElements)
	{
		i.SetGridPosition(sf::Vector2i(i.GetGridPosition().x - x, i.GetGridPosition().y - y));
		i.SetPosition(sf::Vector2f(i.GetPosition().x - x * BLOCK_SIZE, i.GetPosition().y - y * BLOCK_SIZE));
	}
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
	std::filesystem::path mapPath(mPath);
	std::string baseName = mapPath.stem().string(); 
	
	// Always save to assets/maps, regardless of current path structure
	std::string mapFolderPath = "assets/maps/" + baseName;
	std::string texturesFolderPath = mapFolderPath + "/textures";
	
	std::filesystem::create_directories(texturesFolderPath);
	
	// Remove old texture files
	if (std::filesystem::exists(texturesFolderPath))
	{
		for (const auto& entry : std::filesystem::directory_iterator(texturesFolderPath))
		{
			if (entry.is_regular_file())
			{
				try {
					std::filesystem::remove(entry.path());
				}
				catch (const std::filesystem::filesystem_error& e) {
					std::cerr << "Warning: Could not remove old texture file " << entry.path() << ": " << e.what() << std::endl;
				}
			}
		}
	}
	
	std::set<std::string> usedTextures;
	for (const auto &signature : mSignatures)
	{
		usedTextures.insert(signature.second);
	}
	
	std::map<std::string, std::string> pathMapping;
	for (const std::string &texturePath : usedTextures)
	{
		// Find the actual source file using the same logic as TryLoadTexture
		std::filesystem::path textureFile(texturePath);
		std::string fileName = textureFile.filename().string();
		std::string actualSourcePath;
		
		// Try to find the actual source file
		// 1. Check if the original path exists (absolute path)
		if (std::filesystem::exists(texturePath)) {
			actualSourcePath = texturePath;
		}
		// 2. Try defaultResources
		else {
			std::string defaultPath = "assets/defaultResources/" + fileName;
			if (std::filesystem::exists(defaultPath)) {
				actualSourcePath = defaultPath;
			}
			// 3. Try current map's textures folder (for re-saves)
			else {
				std::string currentMapTexturesPath = mapFolderPath + "/textures/" + fileName;
				if (std::filesystem::exists(currentMapTexturesPath)) {
					actualSourcePath = currentMapTexturesPath;
				}
			}
		}
		
		if (!actualSourcePath.empty())
		{
			std::string destPath = texturesFolderPath + "/" + fileName;
			
			try {
				std::filesystem::copy_file(actualSourcePath, destPath, std::filesystem::copy_options::overwrite_existing);
				pathMapping[texturePath] = "textures/" + fileName;
			}
			catch (const std::filesystem::filesystem_error& e) {
				std::cerr << "Error copying texture file " << actualSourcePath << ": " << e.what() << std::endl;
				pathMapping[texturePath] = texturePath;
			}
		}
		else
		{
			std::cerr << "Warning: Texture file not found: " << texturePath << std::endl;
			pathMapping[texturePath] = texturePath;
		}
	}
	
	std::string newMapFilePath = mapFolderPath + "/" + baseName + ".map";
	std::fstream mapFile;
	mapFile.open(newMapFilePath, std::ios::out);
	
	mapFile << "name=" + mName + "\n";
	mapFile << "format=" + std::to_string((unsigned int)mFormat) + "\n";
	
	for (auto &i : mSignatures)
	{
		std::string newTexturePath = pathMapping[i.second];
		if (mFormat == ExportFormat::BASIC && i.first < 177)
			mapFile << "signature=" << (char)i.first << " " << newTexturePath << '\n';
		else if (mFormat == ExportFormat::ADVANCED)
			mapFile << "signature=" << i.first << " " << newTexturePath << '\n';
	}
	
	mapFile << '\n';
	mapFile << "map=" << '\n';
	if (mFormat == ExportFormat::BASIC)
		mapFile << GetBasicFormat();
	else
		mapFile << GetAdvancedFormat();
	mapFile.close();
	
	// Update the map's path to the new location
	mPath = newMapFilePath;
	
	std::cout << "Map saved to: " << newMapFilePath << std::endl;
	std::cout << "Textures copied to: " << texturesFolderPath << std::endl;
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

void		Map::Render(Window *tWindow, const std::string &profileAssetsPath)
{
	sf::Sprite	mBlockSprite;
	for (auto &i : mElements)
	{
		sf::Texture	*texture = TryLoadTexture(i.GetPath(), mPath, profileAssetsPath);
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
