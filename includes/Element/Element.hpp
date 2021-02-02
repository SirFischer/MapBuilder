#pragma once

#include <SFML/Graphics.hpp>

class Element
{
private:
	sf::Vector2f	mPosition = sf::Vector2f(0,0);
	std::string		mPath;

public:
	Element(std::string tPath);
	~Element();

	/**
	 * Setters
	 **/

	/**
	 * Getters
	 **/
	std::string		GetPath(){return (mPath);}
};

