#include "StateManager.hpp"


StateManager::StateManager(Window *tWindow)
{
	mWindow = tWindow;
	mStates.push(new MenuState(mWindow)); //Entry State
}

StateManager::~StateManager()
{

}

void		StateManager::Run()
{
	StateAction	action = StateAction::POP;
	Data		data;

	while (mStates.size())
	{
		mStates.top()->Init(&data);
		action = mStates.top()->Run();

		switch (action)
		{
		case StateAction::POP:
			delete mStates.top();
			mStates.pop();
			break;

		case StateAction::EDITOR:
			mStates.push(new EditorState(mWindow));
			break;

		case StateAction::PROFILE:
			mStates.push(new ProfileState(mWindow));
			break;

		case StateAction::MENU:
			mStates.push(new MenuState(mWindow));
			break;

		case StateAction::OPTIONS:
			mStates.push(new SettingsState(mWindow));
			break;

		default:
			delete mStates.top();
			mStates.pop();
			break;
		}
	}
}