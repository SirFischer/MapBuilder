#include "EditorState.hpp"

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
	mOptions->GetBackground()->SetBackground(sf::Color::Transparent);
	mOptions->GetBackground()->SetOutlineColor(sf::Color::Black);
	mOptions->GetBackground()->SetOutlineThickness(1.f);
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

	auto btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(1, 94);
	btn->SetPositionPercentage(true, true);
	btn->GetText()->SetString("Back");
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetSize(15);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	btn->SetClickEvent([stateReturnAction, isRunning]{
		*stateReturnAction = StateAction::POP;
		*isRunning = false;
	});
	mf::GUI::AddWidget(btn);
}

void		EditorState::InitSettingsButton()
{
	StateAction					*stateReturnAction = &mStateReturnAction;
	bool						*isRunning = &mIsActive;

	auto btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(20, 94);
	btn->SetPositionPercentage(true, true);
	btn->GetText()->SetString("Settings");
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetSize(15);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	btn->SetClickEvent([stateReturnAction, isRunning]{
		*stateReturnAction = StateAction::EDITOR_SETTINGS;
		*isRunning = false;
	});
	mf::GUI::AddWidget(btn);
}

void		EditorState::InitSaveButton()
{
	Map				*map = &mData->mMap;
	Data			*data = mData;
	auto btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(10, 94);
	btn->SetPositionPercentage(true, true);
	btn->GetText()->SetString("Save");
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetSize(15);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	btn->SetClickEvent([map, data]{
		std::string oldPath = map->GetPath();
		map->SaveToFile();
		std::string newPath = map->GetPath();
		
		// Update profile if the path changed
		if (oldPath != newPath) {
			data->mProfile.UpdateMapPath(oldPath, newPath);
			data->mProfile.SaveToFile();
		}
	});
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
	auto btn = mf::Button::Create();
	btn->SetSize(sf::Vector2f(70, 30));
	btn->GetText()->SetString("Grid: ON");
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetSize(15);
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
	textureLoaderList->SetSize(95, 5);
	textureLoaderList->SetSizePercentage(true, true);
	textureLoaderList->GetBackground()->SetBackground(sf::Color::Transparent);
	mOptions->AddWidget(textureLoaderList);
	
	auto btn = mf::Button::Create();
	btn->SetSize(50, 30);
	btn->GetText()->SetString("Reload");
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetSize(10);
	Element	**elem = &mSelectedElement; 
	btn->SetClickEvent([this, elem]{
		*elem = NULL;
		this->LoadTextures();
	});
	textureLoaderList->AddWidget(btn);
	
	btn = mf::Button::Create();
	btn->SetSize(70, 30);
	btn->GetText()->SetString("Open folder");
	btn->GetText()->LoadFont("assets/fonts/Roboto-Regular.ttf");
	btn->GetText()->SetColor(sf::Color::Black);
	btn->GetText()->SetSize(10);
	std::string path = mData->mProfile.GetAssetsPath();
	btn->SetClickEvent([path]{
		#ifdef WIN32
			
		#else
			if (std::system(std::string("xdg-open " + path).c_str()))
			{
				std::system(std::string("dolphin " + path).c_str());
			}
		#endif
	});
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