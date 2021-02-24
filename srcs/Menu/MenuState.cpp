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
	mProfileList->SetSize(70, 90)->SetSizePercentage(true);
	mProfileList->SetPosition(1, 5)->SetPositionPercentage(true);
	mProfileList->SetBackgroundColor(sf::Color(0,0,0,0))->SetOutlineThickness(1)->SetOutlineColor(sf::Color::Black);
	mProfileList->SetContentPosition(sf::Vector2f(10, 5));
	mf::GUI::AddWidget(mProfileList);

	LoadProfiles();

	mMenuList = mf::List::Create();
	mMenuList->SetSize(25, 90)->SetSizePercentage(true);
	mMenuList->SetPosition(72, 5)->SetPositionPercentage(true);
	mMenuList->SetBackgroundColor(sf::Color::Transparent)->SetOutlineThickness(1)->SetOutlineColor(sf::Color::Black);
	mMenuList->SetContentPosition(sf::Vector2f(20, 5));
	mf::GUI::AddWidget(mMenuList);

	LoadMenu();
}

void		MenuState::InitUI()
{
	mf::GUI::ClearWidgets();

	InitList();
}

void		MenuState::Init(Data *tData)
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
	mWindow->Clear(sf::Color(100, 100, 100, 255));
	
	mf::GUI::Render();
	mWindow->Render();
}