#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "ExportFormat.hpp"

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

	/**
	 * Getters
	 **/
	std::string		GetName(){return (mName);}
};
