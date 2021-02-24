#pragma once

#include "State.hpp"

class EditorSettingsState : public State
{
private:

	mf::List		*mSettingsList;
	
	void			InitGUI();
	void			InitSettingsList();
	void			InitSettingsListContent();
	void			InitFormatButton();
	void			InitBackButton();
public:
	EditorSettingsState(Window *tWindow);
	~EditorSettingsState();

	void			Init(Data *tData);
	void			HandleEvents();
	void			Update();
	void			Render();

};

