#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Profile
{
private:
	std::string		mPath = "assets/profiles/newProfile.profile";
	std::string		mName = "newProfile";

public:
	Profile();
	Profile(std::string tPath);
	~Profile();

	/**
	 * Getters
	 **/
	std::string		GetName(){return (mName);}
	std::string		GetPath(){return (mPath);}
};
