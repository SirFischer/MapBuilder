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
	auto list = mf::List::Create();
	list->SetPosition(10, 120);
	list->SetSize(400, 600);
	list->GetBackground()->SetBackground(sf::Color::Transparent);
	list->SetContentOffset(sf::Vector2f(5, 0));
	list->GetBackground()->SetOutlineColor(sf::Color::Black);
	list->GetBackground()->SetOutlineThickness(1.f);
	mf::GUI::AddWidget(list);
	for (auto &entry : maps)
	{
		Map	map(entry);
		auto btn = mf::Button::Create();
		btn->SetSize(90, 5);
		btn->SetSizePercentage(true, true);
		btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
		btn->GetText()->SetString(map.GetName());
		btn->GetText()->SetSize(15);
		btn->GetText()->SetColor(sf::Color::Black);
		btn->GetText()->SetPos(sf::Vector2f(10, 5));
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

void		ProfileState::InitSaveButton()
{
	Data			*data = mData;
	auto text = mNameText;
	auto btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(10, 94);
	btn->SetPositionPercentage(true, true);
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetString("Save");
	btn->GetText()->SetSize(15);
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
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
	auto btn = mf::Button::Create();
	btn->SetSize(200, 40);
	btn->SetPosition(1, 85);
	btn->SetPositionPercentage(true, true);
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetString("Create new map...");
	btn->GetText()->SetSize(15);
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
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
	mNameText = mf::Text::Create();
	mNameText->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	mNameText->GetText()->SetString(mData->mProfile.GetName());
	mNameText->GetText()->SetColor(sf::Color::White);
	mNameText->GetBackground()->SetBackground(sf::Color::Transparent);
	mNameText->GetBackground()->SetOutlineColor(sf::Color::Black);
	mNameText->GetBackground()->SetOutlineThickness(1);
	mNameText->SetPosition(10, 70);
	mNameText->SetSize(400, 40);
	mNameText->EnableEdit();
	mNameText->SetMaxTextLength(20);
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
