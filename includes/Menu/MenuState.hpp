#pragma once

#include "State.hpp"
#include "ResourceManager.hpp"
#include "fstream"

class MenuState : public State
{
private:
	mf::Button		*mQuitBtn;
	mf::Button		*mProjectBtn;

	std::ofstream 	 mMyfile;

	
public:
	MenuState(Window *tWindow);
	~MenuState();

	void		Init();
	void		HandleEvents();
	void		Update();
	void		Render();
};

