#include "MenuState.hpp"

MenuState::MenuState(Window *tWindow)
{
	mWindow = tWindow;
}

MenuState::~MenuState()
{
}

void		MenuState::Init()
{
	mf::GUI::ClearWidgets();
	mIsActive = true;
	mStateReturnAction = StateAction::POP;
	mWindow->ShowCursor();

	/**
	 * INIT STATE AND GUI
	 **/
	
	mProjectBtn = mf::Button::Create(sf::Color::Green, sf::Color::Cyan);
	mProjectBtn->SetPositionPercentage(true)->SetPosition(45, 40);
	mProjectBtn->SetSize(160, 40);
	StateAction	*actionReturn = &mStateReturnAction;
	bool		*active = &mIsActive;
	mProjectBtn->SetClickEvent([actionReturn, active] {
		*actionReturn = StateAction::GAME;
		*active = false;
	});

	mProjectBtn->SetTextFont(*ResourceManager::LoadFont("assets/fonts/Roboto-Regular.ttf"));
	mProjectBtn->SetTextColor(sf::Color::Black);
	mProjectBtn->SetTextPosition(sf::Vector2f(28, 2));
	mProjectBtn->SetText("Projects");
	
	mQuitBtn = mf::Button::Create(sf::Color::Red, sf::Color::Yellow);
	mQuitBtn->SetPositionPercentage(true)->SetPosition(45, 50);
	mQuitBtn->SetSize(160, 40);
	mQuitBtn->SetClickEvent([actionReturn, active] {
		*actionReturn = StateAction::POP;
		*active = false;
	});

	mQuitBtn->SetTextFont(*ResourceManager::LoadFont("assets/fonts/Roboto-Regular.ttf"));
	mQuitBtn->SetTextColor(sf::Color::Black);
	mQuitBtn->SetTextPosition(sf::Vector2f(50, 2));
	mQuitBtn->SetText("Quit");

	mf::GUI::AddWidget(mProjectBtn);
	mf::GUI::AddWidget(mQuitBtn);
}

void		MenuState::HandleEvents()
{
	sf::Event event;
	while (mWindow->HandleEvent(event))
	{
		mf::GUI::HandleEvent(event);
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			mIsActive = false;
		}
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