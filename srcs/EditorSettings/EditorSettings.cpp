#include "EditorSettingsState.hpp"

EditorSettingsState::EditorSettingsState(Window *tWindow){
	mWindow = tWindow;
}
EditorSettingsState::~EditorSettingsState(){

}


void		EditorSettingsState::Init(Data *tData)
{
	mIsActive = true;
	mWindow->ShowCursor();
	mStateReturnAction = StateAction::POP;
	mData = tData;
	/**
	 * INIT STATE AND GUI
	 **/
	InitGUI();
}

void		EditorSettingsState::HandleEvents()
{
	sf::Event event;
	while (mWindow->HandleEvent(event))
	{
		if (event.type == sf::Event::Resized)
			mWindow->ResetView(true);
		mf::GUI::HandleEvent(event);
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			mIsActive = false;
	}
}

void		EditorSettingsState::Update()
{
	
}

void		EditorSettingsState::Render()
{
	mWindow->Clear(sf::Color(100, 100, 100, 255));
	
	mf::GUI::Render();

	mWindow->Render();
}