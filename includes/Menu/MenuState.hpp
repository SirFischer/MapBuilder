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

	/**
	 * UI
	 **/
	void		InitList();

	void		InitUI();

	mf::List	*mProfileList = NULL;

public:
	MenuState(Window *tWindow);
	~MenuState();

	void		Init(Data *tData);
	void		HandleEvents();
	void		Update();
	void		Render();
};

