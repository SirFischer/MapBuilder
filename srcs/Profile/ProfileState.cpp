#include "ProfileState.hpp"

ProfileState::ProfileState(Window *tWindow)
{
	mWindow = tWindow;
}

ProfileState::~ProfileState()
{
}


void		ProfileState::Init(Data *tData)
{
    mf::GUI::ClearWidgets();
	mIsActive = true;
	mStateReturnAction = StateAction::POP;
	mWindow->ShowCursor();
	mData = tData;
}

void		ProfileState::HandleEvents()
{
    sf::Event event;
	while (mWindow->HandleEvent(event))
	{
		if (event.type == sf::Event::Resized)
			mWindow->ResetView(true);
		mf::GUI::HandleEvent(event);
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			mIsActive = false;
		}
	}
}

void		ProfileState::Update()
{

}

void		ProfileState::Render()
{
    mWindow->Clear(sf::Color::Black);
	
	mf::GUI::Render();
	mWindow->Render();
}
