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
	void		InitConfirmBox();
	void		InitDeleteButton();
    void		InitUI();
	
	std::shared_ptr<mf::List>	mConfirmBox = nullptr;
	std::shared_ptr<mf::Text>	mNameText = nullptr;
	
public:
    ProfileState(Window *tWindow);
    ~ProfileState();

    void		Init(Data *tData);
	void		HandleEvents();
	void		Update();
	void		Render();
};