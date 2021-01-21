#pragma once

#include "State.hpp"
#include "ResourceManager.hpp"

class ProfileState : public State

{
private:
    void		InitUI();
	
public:
    ProfileState(Window *tWindow);
    ~ProfileState();

    void		Init(Data *tData);
	void		HandleEvents();
	void		Update();
	void		Render();
};