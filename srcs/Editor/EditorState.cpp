#include "EditorState.hpp"

EditorState::EditorState(Window *tWindow)
{
	mWindow = tWindow;
}

EditorState::~EditorState()
{
}

void		EditorState::InitTextures()
{
	//LOAD ALL TEXTURES INTO OPTIONS
	mTextures = mf::List::Create();
	mTextures->SetSize(95, 40)->SetSizePercentage(true)
	->SetContentPosition(sf::Vector2f(10, 5))
	->SetBackgroundColor(sf::Color::White)
	->SetItemDirection(mf::List::eListDirection::HORIZONTAL)
	->SetContentOverflow(mf::List::eOverflow::WRAP)
	->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1.f);
	mOptions->AddWidget(mTextures);
	LoadTextures();
}

void		EditorState::LoadTextures()
{
	mTextures->ClearWidgets();
	LoadTexturesFromFolder(DEFAULT_RESOURCES);
	LoadTexturesFromFolder(mData->mProfile.GetAssetsPath());
}

void		EditorState::LoadTexturesFromFolder(std::string tPath)
{
	Element	**elementCurrent = &mSelectedElement;
	if (!std::filesystem::exists(tPath))
		return ;
	for (const auto &entry : std::filesystem::directory_iterator(tPath))
	{
		//LOAD DEFAULT TEXTURES
		if (!entry.exists())
			break ;
		mElementList.push_back(Element(entry.path()));
		mf::Button	*btn = mf::Button::Create(entry.path(), entry.path());
		btn->SetSize(sf::Vector2f(50, 50))
		->SetOutlineColor(sf::Color::Black);
		btn->AddEventListener(mf::eEvent::ENTERED, [btn] {
			btn->SetOutlineThickness(1);
		});
		btn->AddEventListener(mf::eEvent::EXITED, [btn] {
			btn->SetOutlineThickness(0);
		});
		int num = mElementList.size();
		std::vector<Element>	*list = &mElementList;
		btn->SetClickEvent([elementCurrent, num, list]{
			*elementCurrent = &(*list)[num - 1];
		});
		mTextures->AddWidget(btn);
	}
}



void		EditorState::InitElementPlacer()
{
	std::list<Element>	*list = &mMapElements;
	Window	*win = mWindow;
	float	*size = &mGridCellSize;
	Element	**curr = &mSelectedElement;
	sf::Vector2f	*position = &mEditorPosition;
	mEditor->SetEventListener(mf::eEvent::LEFT_CLICK, [list, win, size, curr, position] {
		if (!*curr)
			return;
		sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*win->GetRenderWindow()));
		pos += *position;
		(*curr)->SetGridPosition(sf::Vector2i(pos.x / *size, pos.y / *size));
		pos.x = pos.x - ((int)pos.x % (int)*size);
		pos.y = pos.y - ((int)pos.y % (int)*size);
		(*curr)->SetPosition(pos);
		list->push_back(**curr);
		std::cout << "block added to: " << pos.x  << " - " << pos.y << '\n';
	});
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
	InputManager::LoadDefaultKeyBindings();
}

void		EditorState::HandleEvents()
{
	sf::Event event;
	while (mWindow->HandleEvent(event))
	{
		InputManager::HandleInput(event);
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
	if (mSelectedElement != NULL && mSelectedElement != mPreviousSelectedElement)
	{
		mElementEditor->ClearWidgets();
		mf::Image		*img = mf::Image::Create(mSelectedElement->GetPath());
		img->SetSize(60, 60);
		std::cout << mSelectedElement->GetPath() << "\n";
		mElementEditor->AddWidget(img);
		mPreviousSelectedElement = mSelectedElement;
	}
	if (mSelectedElement)
	{
		sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*(mWindow->GetRenderWindow())));
		pos += mEditorPosition;
		pos.x /= mGridCellSize;
		pos.y /= mGridCellSize;
		
		mPhantomSprite.setPosition((int)pos.x * mGridCellSize, (int)pos.y * mGridCellSize);
		sf::Texture		*texture = ResourceManager::LoadTexture(mSelectedElement->GetPath());
		mPhantomSprite.setTexture(*texture);
		mPhantomSprite.setScale(sf::Vector2f(mGridCellSize / texture->getSize().x, mGridCellSize / texture->getSize().y));
		mPhantomSprite.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
		mPhantomSprite.setColor(sf::Color(255, 255, 255, 100));
	}
	if (InputManager::IsActive(InputAction::MOVE_LEFT))
		mEditorPosition.x -= mGridCellSize / 64.f;
	if (InputManager::IsActive(InputAction::MOVE_RIGHT))
		mEditorPosition.x += mGridCellSize / 64.f;
	if (InputManager::IsActive(InputAction::MOVE_DOWN))
		mEditorPosition.y += mGridCellSize / 64.f;
	if (InputManager::IsActive(InputAction::MOVE_UP))
		mEditorPosition.y -= mGridCellSize / 64.f;

}

void		EditorState::Render()
{
	mWindow->Clear(sf::Color(100, 100, 100, 255));

	//RENDER YOUR STUFF
	
	mf::GUI::Render();
	mView = *mEditor->GetView(mWindow->GetRenderWindow());
	
	mView.setCenter((mEditorPosition) + (mEditor->GetSize() / 2.f) + mEditor->GetPosition());
	mWindow->SetView(mView);
	RenderMap();
	mWindow->Draw(mPhantomSprite);
	mView.setCenter((mEditor->GetSize().x / 2.f) + mEditor->GetPosition().x, (mEditor->GetSize().y / 2.f) + mEditor->GetPosition().y);
	mWindow->SetView(mView);
	if (mGridActive)
		RenderGrid();
	
	mWindow->ResetView(true);

	mWindow->Render();
}

void		EditorState::RenderGrid()
{
	float	x = - ((int)mEditorPosition.x % (int)mGridCellSize);
	float	y = - ((int)mEditorPosition.y % (int)mGridCellSize);
;

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

void		EditorState::RenderMap()
{
	for (auto &i : mMapElements)
	{
		sf::Texture	*texture = ResourceManager::LoadTexture(i.GetPath());
		if (texture)
		{
			mBlockSprite.setTexture(*texture);
			mBlockSprite.setPosition(sf::Vector2f(i.GetGridPosition().x * mGridCellSize, i.GetGridPosition().y * mGridCellSize));
			mBlockSprite.setScale(sf::Vector2f(mGridCellSize / texture->getSize().x, mGridCellSize / texture->getSize().y));
			mBlockSprite.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
			mWindow->Draw(mBlockSprite);
		}
	}
}