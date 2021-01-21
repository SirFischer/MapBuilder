#pragma once

#include "Window.hpp"
#include "StateAction.hpp"
#include "Data.hpp"

class State
{

protected:
	sf::Time		mDeltaTime = sf::seconds(1.f / 128.f);
	StateAction		mStateReturnAction = StateAction::POP;

	bool			mIsActive = true;
	Window			*mWindow = NULL;

	Data			*mData = NULL;


public:

	virtual				~State() {}

	virtual void		Init(Data *tData) = 0;
	virtual StateAction	Run();
	virtual void		HandleEvents() = 0;
	virtual void		Update() = 0;
	virtual void		Render() = 0;

};


