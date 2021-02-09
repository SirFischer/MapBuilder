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


