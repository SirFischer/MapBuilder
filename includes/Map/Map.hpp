#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <filesystem>
#include <set>

#include "ExportFormat.hpp"
#include "Element.hpp"
#include "ResourceManager.hpp"
#include "Window.hpp"

#define MAP_PATH "assets/maps/"

#define BLOCK_SIZE 100.f

class Map
{
private:
	std::string							mPath;
	std::string							mName = "NewMap";
	ExportFormat						mFormat = ExportFormat::BASIC;

	std::list<Element>					mElements;

	std::map<int, std::string>			mSignatures;

	void				Load();
	std::string			GetBasicFormat();
	std::string			GetAdvancedFormat();

	void				SortElements();
	void				NormalizeElements();
	void				ReadBasicFormat(std::fstream &tFile);
	void				ReadAdvancedFormat(std::fstream &tFile);
	
public:
	Map(std::string tPath);
	Map();
	~Map();

	void				SaveToFile();

	void				AddElement(Element *tElement);
	void				RemoveElement(sf::Vector2i tPos);

	void				Render(Window *tWindow, const std::string &profileAssetsPath = "");

	/**
	 * Getters
	 **/
	std::string			GetName(){return (mName);}
	std::string			GetPath(){return (mPath);}
	ExportFormat		GetFormat(){return (mFormat);}

	/**
	 * Setters
	 **/
	void				SetFormat(ExportFormat tFormat){mFormat = tFormat;}
};
