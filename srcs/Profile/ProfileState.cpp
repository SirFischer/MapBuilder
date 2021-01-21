#include "ProfileState.hpp"

ProfileState::ProfileState(Window *tWindow)
{
	mWindow = tWindow;
}

ProfileState::~ProfileState()
{
}


void		ProfileState::InitUI()
{
	mf::GUI::ClearWidgets();
	mf::Text	*nameText = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", mData->mProfile.GetName());
	nameText->SetTextColor(sf::Color::White);
	nameText->SetBackgroundColor(sf::Color::Transparent)->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1);
	nameText->SetPosition(10, 10)->SetSize(400, 40);
	nameText->EnableEdit()->SetMaxTextLength(20);
	mf::GUI::AddWidget(nameText);
}

void		ProfileState::Init(Data *tData)
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
    mWindow->Clear(sf::Color(100, 100, 100, 255));
	
	mf::GUI::Render();
	mWindow->Render();
}
