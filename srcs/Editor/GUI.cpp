#include "EditorState.hpp"

void		EditorState::InitGUI()
{
	mf::GUI::ClearWidgets();
	//Editor View
	mEditor = EditorWidget::Create();
	mf::GUI::AddWidget(mEditor);

	//Options
	mOptions = mf::List::Create();
	mOptions->SetPosition(75, 5)->SetPositionPercentage(true);
	mOptions->SetSize(23, 90)->SetSizePercentage(true);
	mOptions->SetContentPosition(sf::Vector2f(10, 5));
	mOptions->SetBackgroundColor(sf::Color::Transparent);
	mOptions->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1.f);
	mf::GUI::AddWidget(mOptions);

	InitOptions();
	InitBackButton();
}


void		EditorState::InitBackButton()
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

void		EditorState::InitOptions()
{
	mOptions->ClearWidgets();
	InitTextures();
	InitTextureLoader();
	InitElementEditor();
	InitGridActivationButton();
	mf::Text	*gridSizeSliderLabel = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", "Grid Size:");
	gridSizeSliderLabel->SetBackgroundColor(sf::Color::Transparent);
	gridSizeSliderLabel->SetCharacterSize(15);
	gridSizeSliderLabel->SetSize(200, 20);
	mOptions->AddWidget(gridSizeSliderLabel);
	mGridSizeSlider = mf::Slider::Create();
	mGridSizeSlider->SetSize(300, 30);
	mGridSizeSlider->SetValue(0.5);
	mGridSizeSlider->GetButton()->SetSize(sf::Vector2f(30, 30));
	mOptions->AddWidget(mGridSizeSlider);
}


void			EditorState::InitGridActivationButton()
{
	bool	*gridActive = &mGridActive;
	mf::Button	*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
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
	textureLoaderList->SetItemDirection(mf::List::eListDirection::HORIZONTAL);
	textureLoaderList->SetSize(95, 5)->SetSizePercentage(true);
	textureLoaderList->SetBackgroundColor(sf::Color::Transparent);
	mOptions->AddWidget(textureLoaderList);
	mf::Button	*btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	btn->SetSize(50, 30);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Reload")->SetCharacterSize(10)->SetTextColor(sf::Color::Black);
	btn->SetClickEvent([this]{
		this->LoadTextures();
	});
	textureLoaderList->AddWidget(btn);
	btn = mf::Button::Create(sf::Color::White, sf::Color::Yellow);
	btn->SetSize(70, 30);
	btn->SetTextFont("assets/fonts/Roboto-Regular.ttf")->SetText("Open folder")->SetCharacterSize(10)->SetTextColor(sf::Color::Black);
	btn->SetClickEvent([]{
		#ifdef WIN32

		#else
			if (std::system("xdg-open assets/defaultResources"))
			{
				std::system("dolphin assets/defaultResources");
			}
		#endif
	});
	textureLoaderList->AddWidget(btn);
	
}


void			EditorState::InitElementEditor()
{
	mElementEditor = mf::List::Create();
	mElementEditor->SetSize(sf::Vector2f(95, 30))->SetSizePercentage(true);
	mElementEditor->SetBackgroundColor(sf::Color::Transparent);
	mElementEditor->SetOutlineColor(sf::Color(125, 125, 125, 255));
	mElementEditor->SetOutlineThickness(1);
	mElementEditor->SetContentPosition(sf::Vector2f(5, 0));
	mOptions->AddWidget(mElementEditor);
	InitElementPlacer();
}