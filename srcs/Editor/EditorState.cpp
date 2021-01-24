#include "EditorState.hpp"

EditorState::EditorState(Window *tWindow)
{
	mWindow = tWindow;
	mWindow->HideCursor();
}

EditorState::~EditorState()
{
	mWindow->ShowCursor();
}

void		EditorState::Init(Data *tData)
{
	mf::GUI::ClearWidgets();
	mIsActive = true;
	mStateReturnAction = StateAction::POP;
	mData = tData;
	/**
	 * INIT STATE AND GUI
	 **/
	mEditor = EditorWidget::Create();
	mf::GUI::AddWidget(mEditor);
	std::cout << mData->mMap.GetName() << std::endl;
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