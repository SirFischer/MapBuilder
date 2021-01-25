#include "EditorState.hpp"

EditorState::EditorState(Window *tWindow)
{
	mWindow = tWindow;
}

EditorState::~EditorState()
{
}

void		EditorState::InitOptions()
{
	mf::Text	*gridSizeSliderLabel = mf::Text::Create("assets/fonts/Roboto-Regular.ttf", "Grid Size:");
	gridSizeSliderLabel->SetBackgroundColor(sf::Color::Transparent);
	gridSizeSliderLabel->SetSize(200, 30);
	mOptions->AddWidget(gridSizeSliderLabel);
	mGridSizeSlider = mf::Slider::Create();
	mGridSizeSlider->SetSize(300, 40);
	mGridSizeSlider->SetValue(0.5);
	mOptions->AddWidget(mGridSizeSlider);
}


void		EditorState::InitGUI()
{
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
}


void		EditorState::Init(Data *tData)
{
	mf::GUI::ClearWidgets();
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