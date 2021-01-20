#pragma once

#include <SFML/Graphics.hpp>
#include "mfGUI.hpp"

class Window
{
private:
	sf::RenderWindow	mWindow;
	/****************************
	 * Change window title here *
	 ****************************/
	std::string			mTitle = "SFML Template Project";
	
	bool				mFullscreen = false;
	sf::VideoMode		mMode = sf::VideoMode(1600, 900);

public:
					Window(/* args */);
					~Window();


	/**
	 * Creation and destruction of window
	 **/
	void			Create();
	void			Destroy();


	/**
	 * Basic drawing utilities
	 **/
	void			Draw(sf::Drawable &tDrawable);
	void			Clear();
	void			Clear(sf::Color tColor);
	void			Render();

	/**
	 * Events
	 **/
	bool			HandleEvent(sf::Event &tEvent);


	/**
	 * Controls
	 **/
	void			ToggleFullscreen();
	void			ChangeResolution(int tWidth, int tHeight);
	void			HideCursor();
	void			ShowCursor();

	/**
	 * View
	 **/
	void			ResetView(bool tResize);

	/**
	 * Setters
	 **/
	void			SetView(sf::View tView);

	/**
	 * Getters
	 **/
	bool			IsOpen(){return (mWindow.isOpen());}
	sf::Vector2u	GetSize(){return (mWindow.getSize());}
	sf::View		GetCurrentView(){return (mWindow.getView());}
};
