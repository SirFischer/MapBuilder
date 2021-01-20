#include "EditorState.hpp"

EditorState::EditorState(Window *tWindow)
{
	mWindow = tWindow;
	mWindow->HideCursor();
}

EditorState::~EditorState()
{
	mWindow->ShowCursor();
}

void		EditorState::Init()
{
	mf::GUI::ClearWidgets();
	mIsActive = true;
	mStateReturnAction = StateAction::POP;

	/**
	 * INIT STATE AND GUI
	 **/
}

void		EditorState::HandleEvents()
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

void		EditorState::Update()
{
	
}

void		EditorState::Render()
{
	mWindow->Clear(sf::Color::Green);

	//RENDER YOUR STUFF
	
	mf::GUI::Render();
	mWindow->Render();
}