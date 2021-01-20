#include "MenuState.hpp"

MenuState::MenuState(Window *tWindow)
{
	mWindow = tWindow;
}

MenuState::~MenuState()
{
}

void		MenuState::InitList()
{
	mProfileList = mf::List::Create();
	mf::GUI::AddWidget(mProfileList);

	mf::Text	*text = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", "test");
	text->SetTextColor(sf::Color::Black)->SetSize(200, 40);
	mProfileList->AddWidget(text);
	text = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", "test2");
	text->SetTextColor(sf::Color::Black)->SetSize(200, 40);
	mProfileList->AddWidget(text);
	text = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", "test3");
	text->SetTextColor(sf::Color::Black)->SetSize(200, 40);
	mProfileList->AddWidget(text);
}

void		MenuState::InitUI()
{
	mf::GUI::ClearWidgets();

	InitList();
}

void		MenuState::Init()
{
	mIsActive = true;
	mStateReturnAction = StateAction::POP;
	mWindow->ShowCursor();

	/**
	 * INIT STATE AND GUI
	 **/
	
	InitUI();
}

void		MenuState::HandleEvents()
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

void		MenuState::Update()
{
	
}

void		MenuState::Render()
{
	mWindow->Clear(sf::Color::Black);
	
	mf::GUI::Render();
	mWindow->Render();
}