#pragma once

#include "State.hpp"
#include "ResourceManager.hpp"
#include "fstream"

class MenuState : public State
{
private:

	std::ofstream 	 mMyfile;

	/**
	 * UI
	 **/
	void		InitList();

	void		InitUI();

public:
	MenuState(Window *tWindow);
	~MenuState();

	void		Init();
	void		HandleEvents();
	void		Update();
	void		Render();
};

