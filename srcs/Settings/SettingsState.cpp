#include "SettingsState.hpp"

SettingsState::SettingsState(Window *tWindow)
{
	mWindow = tWindow;
}

SettingsState::~SettingsState()
{
}

void		SettingsState::InitBackButton()
{
	StateAction					*stateReturnAction = &mStateReturnAction;
	bool						*isRunning = &mIsActive;

	auto btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(1, 94);
	btn->SetPositionPercentage(true, true);
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetString("Back");
	btn->GetText()->SetSize(15);
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	btn->SetClickEvent([stateReturnAction, isRunning]{
		*stateReturnAction = StateAction::POP;
		*isRunning = false;
	});
	mf::GUI::AddWidget(btn);
}


void		SettingsState::InitUI()
{
	mf::GUI::ClearWidgets();

	InitBackButton();
}

void		SettingsState::Init(Data *tData)
{
	mIsActive = true;
	mStateReturnAction = StateAction::POP;
	mWindow->ShowCursor();
	mData = tData;

	/**
	 * INIT STATE AND GUI
	 **/
	
	InitUI();
}

void		SettingsState::HandleEvents()
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

void		SettingsState::Update()
{
	
}

void		SettingsState::Render()
{
	mWindow->Clear(sf::Color(100, 100, 100, 255));
	
	mf::GUI::Render();
	mWindow->Render();
}