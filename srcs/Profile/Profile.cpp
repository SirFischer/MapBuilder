#include "Profile.hpp"

Profile::Profile()
{

}

Profile::Profile(std::string tPath)
{
	mPath = tPath;
	Load();
}

Profile::~Profile()
{
}

void			Profile::SaveToFile()
{
	std::fstream		profileFile;

	profileFile.open(mPath, std::ios::out);
	profileFile << "name=" + mName + "\n";
	profileFile << "assets=" + mAssets + "\n";
	for (auto &map : mMaps)
		profileFile << "map=" << map << "\n";
	profileFile.close();
}

void			Profile::UpdateMapPath(const std::string &oldPath, const std::string &newPath)
{
	for (auto &mapPath : mMaps) {
		if (mapPath == oldPath) {
			mapPath = newPath;
			break;
		}
	}
}

void			Profile::Delete()
{
	std::filesystem::remove_all(mAssets);
	for (auto &map : mMaps)
		std::filesystem::remove(map);
	std::filesystem::remove(mPath);
}


void			Profile::Load()
{
	std::fstream		profileFile;
	std::string			line;

	profileFile.open(mPath, std::ios::in);
	while (std::getline(profileFile, line))
	{
		std::stringstream ss(line);
		std::string token;
		std::getline(ss, token, '=');
		if (token.find("name") != std::string::npos)
		{
			std::getline(ss, token, '=');
			mName = token;
		} else if (token.find("map") != std::string::npos)
		{
			std::getline(ss, token, '=');
			mMaps.push_back(token);
		}else if (token.find("assets") != std::string::npos)
		{
			std::getline(ss, token, '=');
			mAssets = token;
		}
	}
}


