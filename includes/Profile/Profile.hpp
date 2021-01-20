#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Profile
{
private:
	std::string		mPath = "default";
	std::string		mName = "default";

public:
	Profile(std::string tPath);
	~Profile();

	/**
	 * Getters
	 **/
	std::string		GetName(){return (mName);}
	std::string		GetPath(){return (mPath);}
};
