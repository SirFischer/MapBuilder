#include "ProfileState.hpp"

ProfileState::ProfileState(Window *tWindow)
{
	mWindow = tWindow;
}

ProfileState::~ProfileState()
{
}

void		ProfileState::InitMapList()
{
	Data						*data = mData;
	StateAction					*stateReturnAction = &mStateReturnAction;
	bool						*isRunning = &mIsActive;
	std::vector<std::string>	maps = mData->mProfile.GetMaps();
	mf::List		*list = mf::List::Create();
	list->SetPosition(10, 120)->SetSize(400, 600);
	list->SetBackgroundColor(sf::Color::Transparent);
	list->SetContentPosition(sf::Vector2f(5, 0));
	list->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1.f);
	mf::GUI::AddWidget(list);
	for (auto &entry : maps)
	{
		Map	map(entry);
		mf::Button		*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
		btn->SetSize(90, 5)->SetSizePercentage(true);
		btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText(map.GetName())->SetCharacterSize(15)
		->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
		btn->SetClickEvent([data, map, stateReturnAction, isRunning]{
			data->mMap = map;
			*stateReturnAction = StateAction::EDITOR;
			*isRunning = false;
		});
		list->AddWidget(btn);
	}
}

void		ProfileState::InitBackButton()
{
	StateAction					*stateReturnAction = &mStateReturnAction;
	bool						*isRunning = &mIsActive;

	mf::Button		*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	btn->SetSize(100, 40);
	btn->SetPosition(1, 94)->SetPositionPercentage(true);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Back")->SetCharacterSize(15)
	->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
	btn->SetClickEvent([stateReturnAction, isRunning]{
		*stateReturnAction = StateAction::POP;
		*isRunning = false;
	});
	mf::GUI::AddWidget(btn);
}

void		ProfileState::InitSaveButton()
{
	Data			*data = mData;
	mf::Text		*text = mNameText;
	mf::Button		*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	btn->SetSize(100, 40);
	btn->SetPosition(10, 94)->SetPositionPercentage(true);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Save")->SetCharacterSize(15)
	->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
	btn->SetClickEvent([data, text]{
		data->mProfile.SetName(text->GetString());
		data->mProfile.SaveToFile();
	});
	mf::GUI::AddWidget(btn);
}

void		ProfileState::InitCreateButton()
{
	Data			*data = mData;
	StateAction		*stateReturnAction = &mStateReturnAction;
	bool			*isRunning = &mIsActive;
	mf::Button		*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	btn->SetSize(200, 40);
	btn->SetPosition(1, 85)->SetPositionPercentage(true);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Create new map...")->SetCharacterSize(15)
	->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
	btn->SetClickEvent([data, stateReturnAction, isRunning]{
		time_t	t = time(0);
		int random = rand() % 100;
		std::string path = std::string(MAP_PATH) + std::to_string(t) + std::to_string(random) + ".map";
		data->mProfile.AddMap(path);
		data->mProfile.SaveToFile();
		Map map(path);
		map.SaveToFile();
		data->mMap = map;
		*stateReturnAction = StateAction::EDITOR;
		*isRunning = false;
	});
	mf::GUI::AddWidget(btn);
}

void		ProfileState::InitUI()
{
	
	mf::GUI::ClearWidgets();
	mNameText = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", mData->mProfile.GetName());
	mNameText->SetTextColor(sf::Color::White);
	mNameText->SetBackgroundColor(sf::Color::Transparent)->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1);
	mNameText->SetPosition(10, 70)->SetSize(400, 40);
	mNameText->EnableEdit()->SetMaxTextLength(20);
	mf::GUI::AddWidget(mNameText);

	InitBackButton();
	InitMapList();
	InitSaveButton();
	InitCreateButton();
	InitConfirmBox();
	InitDeleteButton();
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
