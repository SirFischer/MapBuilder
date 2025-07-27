#include "EditorState.hpp"
#include "Components.hpp"

void		EditorState::InitGUI()
{
	mf::GUI::ClearWidgets();
	//Editor View
	mEditor = EditorWidget::Create();
	mf::GUI::AddWidget(mEditor);

	//Options
	mOptions = mf::List::Create();
	mOptions->SetPosition(75, 5);
	mOptions->SetPositionPercentage(true, true);
	mOptions->SetSize(23, 90);
	mOptions->SetSizePercentage(true, true);
	mOptions->SetContentOffset(sf::Vector2f(10, 5));
	mOptions->GetBackground()->SetBackground(sf::Color(130, 130, 130));
	mOptions->GetBackground()->SetOutlineColor(sf::Color::Black);
	mOptions->GetBackground()->SetOutlineThickness(1.f);
	mOptions->SetContentOverflow(mf::List::eOverflow::INVISIBLE);
	mf::GUI::AddWidget(mOptions);

	InitOptions();
	InitBackButton();
	InitSaveButton();
	InitSettingsButton();
}


void		EditorState::InitBackButton()
{
	StateAction					*stateReturnAction = &mStateReturnAction;
	bool						*isRunning = &mIsActive;

	auto btn = Components::CreateButton("Back", sf::Vector2f(100, 40), sf::Vector2f(1, 94), [stateReturnAction, isRunning] {
		*stateReturnAction = StateAction::POP;
		*isRunning = false;
	});
	btn->SetPositionPercentage(true, true);
	mf::GUI::AddWidget(btn);
}

void		EditorState::InitSettingsButton()
{
	StateAction					*stateReturnAction = &mStateReturnAction;
	bool						*isRunning = &mIsActive;

	auto btn = Components::CreateButton("Settings", sf::Vector2f(100, 40), sf::Vector2f(20, 94), [stateReturnAction, isRunning] {
		*stateReturnAction = StateAction::EDITOR_SETTINGS;
		*isRunning = false;
	});
	btn->SetPositionPercentage(true, true);
	mf::GUI::AddWidget(btn);
}

void		EditorState::InitSaveButton()
{
	Map				*map = &mData->mMap;
	auto btn = Components::CreateButton("Save", sf::Vector2f(100, 40), sf::Vector2f(10, 94), [map] {
		map->SaveToFile();
	});
	btn->SetPositionPercentage(true, true);
	mf::GUI::AddWidget(btn);
}


void		EditorState::InitOptions()
{
	mOptions->ClearWidgets();
	InitTextures();
	InitTextureLoader();
	InitElementEditor();
	InitGridActivationButton();
}


void			EditorState::InitGridActivationButton()
{
	bool	*gridActive = &mGridActive;
	auto btn = Components::CreateButton("Grid: ON", sf::Vector2f(70, 30), sf::Vector2f(0, 94), [gridActive] {
	});
	btn->SetClickEvent([btn, gridActive]{
		*gridActive = !*gridActive;
		btn->GetText()->SetString((((*gridActive) ? "Grid: ON" : "Grid: OFF")));
	});
	mOptions->AddWidget(btn);
}

void			EditorState::InitTextureLoader()
{
	auto textureLoaderList = mf::List::Create();
	textureLoaderList->SetItemDirection(mf::eDirection::HORIZONTAL);
	textureLoaderList->SetSize(95, 50);
	textureLoaderList->SetSizePercentage(true, false);
	textureLoaderList->GetBackground()->SetBackground(sf::Color::Transparent);
	mOptions->AddWidget(textureLoaderList);
	
	Element	**elem = &mSelectedElement;
	auto btn = Components::CreateButton("Load", sf::Vector2f(50, 30), sf::Vector2f(0, 0), [this, elem] {
		*elem = NULL;
		this->LoadTextures();
	});
	btn->GetText()->SetSize(10);
	textureLoaderList->AddWidget(btn);
	
	std::string path = mData->mProfile.GetAssetsPath();
	btn = Components::CreateButton("Open folder", sf::Vector2f(70, 30), sf::Vector2f(0, 0), [path] {
		#ifdef WIN32
			std::system(std::string("explorer " + path).c_str());
		#else
			std::system(std::string("xdg-open " + path).c_str());
		#endif
	});
	btn->GetText()->SetSize(10);
	textureLoaderList->AddWidget(btn);
}


void			EditorState::InitElementEditor()
{
	mElementEditor = mf::List::Create();
	mElementEditor->SetSize(95, 30);
	mElementEditor->SetSizePercentage(true, true);
	mElementEditor->GetBackground()->SetBackground(sf::Color::Transparent);
	mElementEditor->GetBackground()->SetOutlineColor(sf::Color(125, 125, 125, 255));
	mElementEditor->GetBackground()->SetOutlineThickness(1);
	mElementEditor->SetContentOffset(sf::Vector2f(5, 0));
	mOptions->AddWidget(mElementEditor);
	InitElementPlacer();
}