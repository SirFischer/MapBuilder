#include "EditorState.hpp"

EditorState::EditorState(Window *tWindow)
{
	mWindow = tWindow;
}

EditorState::~EditorState()
{
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
	InitTextures();
	mf::Text	*gridSizeSliderLabel = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", "Grid Size:");
	gridSizeSliderLabel->SetBackgroundColor(sf::Color::Transparent);
	gridSizeSliderLabel->SetSize(200, 30);
	mOptions->AddWidget(gridSizeSliderLabel);
	mGridSizeSlider = mf::Slider::Create();
	mGridSizeSlider->SetSize(300, 40);
	mGridSizeSlider->SetValue(0.5);
	mOptions->AddWidget(mGridSizeSlider);
}

void		EditorState::InitTextures()
{
	//LOAD ALL TEXTURES INTO OPTIONS
	mTextures = mf::List::Create();
	mTextures->SetSize(95, 40)->SetSizePercentage(true);
	mTextures->SetContentPosition(sf::Vector2f(10, 5));
	mTextures->SetBackgroundColor(sf::Color::White);
	mTextures->SetItemDirection(mf::List::eListDirection::HORIZONTAL);
	mTextures->SetContentOverflow(mf::List::eOverflow::WRAP);
	mTextures->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1.f);
	mOptions->AddWidget(mTextures);

	for (const auto &entry : std::filesystem::directory_iterator(DEFAULT_RESOURCES))
	{
		//LOAD DEFAULT TEXTURES
		mf::Image	*img = mf::Image::Create(entry.path());
		img->SetSize(sf::Vector2f(50, 50));
		mTextures->AddWidget(img);
	}
}


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


void		EditorState::Init(Data *tData)
{
	mIsActive = true;
	mWindow->ShowCursor();
	mStateReturnAction = StateAction::POP;
	mData = tData;
	/**
	 * INIT STATE AND GUI
	 **/
	InitGUI();
}

void		EditorState::HandleEvents()
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

void		EditorState::Update()
{
	mGridCellSize = (std::clamp(mGridSizeSlider->GetValue(), 0.f, 1.f) * 100) + 10;
}

void		EditorState::Render()
{
	mWindow->Clear(sf::Color(100, 100, 100, 255));

	//RENDER YOUR STUFF
	
	mf::GUI::Render();
	mWindow->SetView(*mEditor->GetView(mWindow->GetRenderWindow()));
	RenderGrid();
	mWindow->ResetView(true);

	mWindow->Render();
}

void		EditorState::RenderGrid()
{
	float	x = 0;
	float	y = 0;

	while (y < mWindow->GetSize().y)
	{
		mLine[0].position = sf::Vector2f(0, y);
		mLine[1].position = sf::Vector2f(mWindow->GetSize().x, y);
		mWindow->Draw(mLine, 2, sf::Lines);
		y += mGridCellSize;
	}
	while (x < mWindow->GetSize().x)
	{
		mLine[0].position = sf::Vector2f(x, 0);
		mLine[1].position = sf::Vector2f(x, mWindow->GetSize().y);
		mWindow->Draw(mLine, 2, sf::Lines);
		x += mGridCellSize;
	}
}