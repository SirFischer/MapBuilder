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
	std::string					mAssets = "assets/profileAssets/newProfile";
	std::string					mName = "newProfile";
	std::vector<std::string>	mMaps;

	void						Load();
public:
	Profile();
	Profile(std::string tPath);
	~Profile();

	/**
	 * Getters
	 **/
	std::string					GetName(){return (mName);}
	std::string					GetPath(){return (mPath);}
	std::string					GetAssetsPath(){return (mAssets);}
	std::vector<std::string>	GetMaps(){return (mMaps);}
};
