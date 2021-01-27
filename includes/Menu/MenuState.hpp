#pragma once

#include <filesystem>

#include "State.hpp"
#include "ResourceManager.hpp"
#include "Profile.hpp"

#define PROFILE_DIR_PATH "assets/profiles"

class MenuState : public State
{
private:

	void		LoadProfiles();
	void		LoadMenu();

	/**
	 * UI
	 **/
	void		InitList();

	void		InitUI();

	mf::List	*mProfileList = NULL;
	mf::List	*mMenuList = NULL;

public:
	MenuState(Window *tWindow);
	~MenuState();

	void		Init(Data *tData);
	void		HandleEvents();
	void		Update();
	void		Render();
};

