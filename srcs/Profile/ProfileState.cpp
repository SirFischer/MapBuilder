#include "ProfileState.hpp"
#include "Components.hpp"

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
		auto btn = Components::CreateButton(map.GetName(), sf::Vector2f(90, 5), sf::Vector2f(0, 0), [data, map, stateReturnAction, isRunning]{
			data->mMap = map;
			*stateReturnAction = StateAction::EDITOR;
			*isRunning = false;
		});
		btn->SetSizePercentage(true, true);
		list->AddWidget(btn);
	}
}

void		ProfileState::InitBackButton()
{
	StateAction					*stateReturnAction = &mStateReturnAction;
	bool						*isRunning = &mIsActive;

	auto btn = Components::CreateButton("Back", sf::Vector2f(100, 40), sf::Vector2f(1, 94), [stateReturnAction, isRunning]{
		*stateReturnAction = StateAction::POP;
		*isRunning = false;
	});
	btn->SetPositionPercentage(true, true);
	mf::GUI::AddWidget(btn);
}

void		ProfileState::InitSaveButton()
{
	Data			*data = mData;
	auto text = mNameText;
	auto btn = Components::CreateButton("Save", sf::Vector2f(100, 40), sf::Vector2f(10, 94), [data, text]{
		data->mProfile.SetName(text->GetString());
		data->mProfile.SaveToFile();

	});
	btn->SetPositionPercentage(true, true);
	mf::GUI::AddWidget(btn);
}

void		ProfileState::InitCreateButton()
{
	Data			*data = mData;
	StateAction		*stateReturnAction = &mStateReturnAction;
	bool			*isRunning = &mIsActive;

	auto btn = Components::CreateButton("Create new map", sf::Vector2f(200, 40), sf::Vector2f(1, 85), [data, stateReturnAction, isRunning]{
		time_t	t = time(0);
		int random = rand() % 100;
		std::string initialPath = std::string(MAP_PATH) + std::to_string(t) + std::to_string(random) + ".map";
		
		Map map(initialPath);
		map.SaveToFile();
		
		data->mProfile.AddMap(map.GetPath());
		data->mProfile.SaveToFile();
		
		data->mMap = map;
		*stateReturnAction = StateAction::EDITOR;
		*isRunning = false;
	});
	btn->SetPositionPercentage(true, true);
	mf::GUI::AddWidget(btn);
}

void		ProfileState::InitUI()
{
	mf::GUI::ClearWidgets();
	mNameText = mf::Text::Create();
	mNameText->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	mNameText->GetText()->SetString(mData->mProfile.GetName());
	mNameText->GetText()->SetColor(sf::Color::Black);
	mNameText->GetBackground()->SetBackground(sf::Color::White);
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
	mf::GUI::Update();
}

void		ProfileState::Render()
{
    mWindow->Clear(sf::Color(100, 100, 100, 255));
	
	mf::GUI::Render();
	mWindow->Render();
}
