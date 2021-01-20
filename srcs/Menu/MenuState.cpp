#include "MenuState.hpp"

MenuState::MenuState(Window *tWindow)
{
	mWindow = tWindow;
}

MenuState::~MenuState()
{
}

void		MenuState::LoadProfiles()
{
	for (const auto &entry : std::filesystem::directory_iterator(PROFILE_DIR_PATH))
	{
		Profile profile(entry.path());
		mf::Button		*btn = mf::Button::Create(sf::Color::Green, sf::Color::Yellow);
		btn->SetSize(90, 5)->SetSizePercentage(true);
		btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText(profile.GetName())
		->SetCharacterSize(15)->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
		mProfileList->AddWidget(btn);
	}
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
	mWindow->Clear(sf::Color(100, 100, 100, 255));
	
	mf::GUI::Render();
	mWindow->Render();
}