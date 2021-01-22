#pragma once

#include "State.hpp"
#include "ResourceManager.hpp"
#include "Map.hpp"

class ProfileState : public State

{
private:
	void		InitMapList();
	void		InitBackButton();
    void		InitUI();
	
public:
    ProfileState(Window *tWindow);
    ~ProfileState();

    void		Init(Data *tData);
	void		HandleEvents();
	void		Update();
	void		Render();
};