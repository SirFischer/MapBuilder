#pragma once

#include "State.hpp"
#include "ResourceManager.hpp"

class ProfileState : public State

{
private:
    /* data */
public:
    ProfileState(Window *tWindow);
    ~ProfileState();

    void		Init();
	void		HandleEvents();
	void		Update();
	void		Render();
};