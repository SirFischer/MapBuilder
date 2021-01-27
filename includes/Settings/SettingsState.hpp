#pragma once

#include <filesystem>

#include "State.hpp"
#include "ResourceManager.hpp"

class SettingsState : public State
{
private:

	/**
	 * UI
	 **/
	void		InitBackButton();

	void		InitUI();

public:
	SettingsState(Window *tWindow);
	~SettingsState();

	void		Init(Data *tData);
	void		HandleEvents();
	void		Update();
	void		Render();
};

