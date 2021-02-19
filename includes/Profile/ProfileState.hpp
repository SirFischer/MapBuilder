#pragma once

#include <time.h>
#include <random>

#include "State.hpp"
#include "ResourceManager.hpp"
#include "Map.hpp"

class ProfileState : public State

{
private:
	void		InitMapList();
	void		InitBackButton();
	void		InitSaveButton();
	void		InitCreateButton();
    void		InitUI();

	mf::Text	*mNameText;
	
public:
    ProfileState(Window *tWindow);
    ~ProfileState();

    void		Init(Data *tData);
	void		HandleEvents();
	void		Update();
	void		Render();
};