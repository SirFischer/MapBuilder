#include "Profile.hpp"

Profile::Profile(std::string tPath)
{
	std::fstream		profileFile;
	std::string			line;

	mPath = tPath;
	profileFile.open(tPath, std::ios::in);
	while (std::getline(profileFile, line))
	{
		std::stringstream ss(line);
		std::string token;
		std::getline(ss, token, ' ');
		if (token == "name")
		{
			std::getline(ss, token, ' ');
			std::getline(ss, token, ' ');
			mName = token;
		}
	}
}

Profile::~Profile()
{
}

