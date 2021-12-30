#include "EditorState.hpp"

void		EditorState::InitGUI()
{
	mf::GUI::ClearWidgets();
	//Editor View
	mEditor = EditorWidget::Create();
	mf::GUI::AddWidget(mEditor);

	//Options
	mOptions = mf::List::Create();
	mOptions->SetPosition(75, 5)->SetPositionPercentage(true, true);
	mOptions->SetSize(23, 90)->SetSizePercentage(true, true);
	mOptions->SetContentOffset(sf::Vector2f(10, 5));
	mOptions->SetBackgroundColor(sf::Color::Transparent);
	mOptions->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1.f);
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

	mf::Button		*btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(1, 94)->SetPositionPercentage(true, true);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Back")->SetCharacterSize(15)
	->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
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

	mf::Button		*btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(20, 94)->SetPositionPercentage(true, true);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Settings")->SetCharacterSize(15)
	->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
	btn->SetClickEvent([stateReturnAction, isRunning]{
		*stateReturnAction = StateAction::EDITOR_SETTINGS;
		*isRunning = false;
	});
	mf::GUI::AddWidget(btn);
}

void		EditorState::InitSaveButton()
{
	Map				*map = &mData->mMap;
	mf::Button		*btn = mf::Button::Create();
	btn->SetSize(100, 40);
	btn->SetPosition(10, 94)->SetPositionPercentage(true, true);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Save")->SetCharacterSize(15)
	->SetTextColor(sf::Color::Black)->SetTextPosition(sf::Vector2f(10, 5));
	btn->SetClickEvent([map]{
		map->SaveToFile();
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
	mf::Button	*btn = mf::Button::Create();
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Grid: ON")->SetCharacterSize(15)->SetTextColor(sf::Color::Black);
	btn->SetSize(sf::Vector2f(70, 30));
	btn->SetClickEvent([btn, gridActive]{
		*gridActive = !*gridActive;
		btn->SetText((((*gridActive) ? "Grid: ON" : "Grid: OFF")));
	});
	mOptions->AddWidget(btn);
}

void			EditorState::InitTextureLoader()
{
	mf::List	*textureLoaderList = mf::List::Create();
	textureLoaderList->SetItemDirection(mf::eDirection::HORIZONTAL);
	textureLoaderList->SetSize(95, 5)->SetSizePercentage(true, true);
	textureLoaderList->SetBackgroundColor(sf::Color::Transparent);
	mOptions->AddWidget(textureLoaderList);
	mf::Button	*btn = mf::Button::Create();
	btn->SetSize(50, 30);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Reload")->SetCharacterSize(10)->SetTextColor(sf::Color::Black);
	Element	**elem = &mSelectedElement; 
	btn->SetClickEvent([this, elem]{
		*elem = NULL;
		this->LoadTextures();
	});
	textureLoaderList->AddWidget(btn);
	btn = mf::Button::Create();
	btn->SetSize(70, 30);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Open folder")->SetCharacterSize(10)->SetTextColor(sf::Color::Black);
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
	mElementEditor->SetSize(sf::Vector2f(95, 30))->SetSizePercentage(true, true);
	mElementEditor->SetBackgroundColor(sf::Color::Transparent);
	mElementEditor->SetOutlineColor(sf::Color(125, 125, 125, 255));
	mElementEditor->SetOutlineThickness(1);
	mElementEditor->SetContentOffset(sf::Vector2f(5, 0));
	mOptions->AddWidget(mElementEditor);
	InitElementPlacer();
}