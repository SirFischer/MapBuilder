#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "ExportFormat.hpp"

#define MAP_PATH "assets/maps/"

class Map
{
private:
	std::string		mPath;
	std::string		mName = "NewMap";
	ExportFormat	mFormat = ExportFormat::BASIC;

	void			Load();
public:
	Map(std::string tPath);
	Map();
	~Map();

	void						SaveToFile();

	/**
	 * Getters
	 **/
	std::string		GetName(){return (mName);}
};
