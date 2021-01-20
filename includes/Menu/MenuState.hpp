#pragma once

#include "State.hpp"
#include "ResourceManager.hpp"

class MenuState : public State
{
private:

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

