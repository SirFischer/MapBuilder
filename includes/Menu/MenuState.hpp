#pragma once

#include <filesystem>
#include <time.h>
#include <random>

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

	std::shared_ptr<mf::List>	mProfileList = nullptr;
	std::shared_ptr<mf::List>	mMenuList = nullptr;

public:
	MenuState(Window *tWindow);
	~MenuState();

	void		Init(Data *tData);
	void		HandleEvents();
	void		Update();
	void		Render();
};

