#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define PROFILE_PATH "assets/profiles/"
#define PROFILE_RESOURCE_PATH "assets/profileAssets/"

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

	void						SaveToFile();

	/**
	 * Setters
	 **/
	void						SetAssetsPath(std::string tPath) {mAssets = tPath;}
	void						SetName(std::string tName) {mName = tName;}

	void						AddMap(std::string tPath){mMaps.push_back(tPath);}
	
	/**
	 * Getters
	 **/
	std::string					GetName(){return (mName);}
	std::string					GetPath(){return (mPath);}
	std::string					GetAssetsPath(){return (mAssets);}
	std::vector<std::string>	GetMaps(){return (mMaps);}
};
