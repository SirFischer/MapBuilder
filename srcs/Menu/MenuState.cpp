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
	mProfileList->SetSize(70, 90);
	mProfileList->SetSizePercentage(true, true);
	mProfileList->SetPosition(1, 5);
	mProfileList->SetPositionPercentage(true, true);
	mProfileList->GetBackground()->SetBackground(sf::Color(120,120,120));
	mProfileList->GetBackground()->SetOutlineThickness(1);
	mProfileList->GetBackground()->SetOutlineColor(sf::Color::Black);
	mProfileList->SetContentOffset(sf::Vector2f(10, 5));
	mf::GUI::AddWidget(mProfileList);

	LoadProfiles();

	mMenuList = mf::List::Create();
	mMenuList->SetSize(25, 90);
	mMenuList->SetSizePercentage(true, true);
	mMenuList->SetPosition(72, 5);
	mMenuList->SetPositionPercentage(true, true);
	mMenuList->GetBackground()->SetBackground(sf::Color(120,120,120));
	mMenuList->GetBackground()->SetOutlineThickness(1);
	mMenuList->GetBackground()->SetOutlineColor(sf::Color::Black);
	mMenuList->SetContentOffset(sf::Vector2f(20, 5));
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