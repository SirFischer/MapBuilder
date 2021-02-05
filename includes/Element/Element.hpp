#pragma once

#include <SFML/Graphics.hpp>

class Element
{
private:
	sf::Vector2f	mPosition = sf::Vector2f(0,0);
	sf::Vector2i	mGridPosition = sf::Vector2i(0,0);
	std::string		mPath;

public:
	Element(std::string tPath);
	~Element();

	/**
	 * Setters
	 **/
	void			SetPosition(sf::Vector2f tPosition) {mPosition = tPosition;}
	void			SetGridPosition(sf::Vector2i tPosition) {mGridPosition = tPosition;}
	/**
	 * Getters
	 **/
	std::string		GetPath(){return (mPath);}
	sf::Vector2f	GetPosition(){return (mPosition);}
	sf::Vector2i	GetGridPosition(){return (mGridPosition);}
};

