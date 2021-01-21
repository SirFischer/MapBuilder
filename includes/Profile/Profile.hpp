#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Profile
{
private:
	std::string					mPath = "assets/profiles/newProfile.profile";
	std::string					mName = "newProfile";
	std::vector<std::string>	mMaps;

public:
	Profile();
	Profile(std::string tPath);
	~Profile();

	/**
	 * Getters
	 **/
	std::string					GetName(){return (mName);}
	std::string					GetPath(){return (mPath);}
	std::vector<std::string>	GetMaps(){return (mMaps);}
};
