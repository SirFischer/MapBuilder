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

	mf::List	*list = mf::List::Create();
	list->SetPosition(10, 100)->SetSize(400, 600);
	list->SetBackgroundColor(sf::Color::Transparent);
	list->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1.f);
	mf::GUI::AddWidget(list);
	std::vector<std::string>	maps = mData->mProfile.GetMaps();
	for (auto &entry : maps)
	{
		mf::Button		*btn = mf::Button::Create(sf::Color::Green, sf::Color::Yellow);
		btn->SetSize(90, 5)->SetSizePercentage(true);
		btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText(entry)->SetCharacterSize(15)
		->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
		list->AddWidget(btn);
	}
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
