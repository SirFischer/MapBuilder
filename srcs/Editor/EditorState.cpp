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
	Map	*map = &mData->mMap;
	Window	*win = mWindow;
	Element	**curr = &mSelectedElement;
	sf::Vector2f	*position = &mEditorPosition;
	mEditor->SetEventListener(mf::eEvent::LEFT_CLICK, [map, win, curr, position] {
		if (!*curr)
			return;
		sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*win->GetRenderWindow()));
		pos += *position;
		if (pos.x <= 0)
			pos.x -= BLOCK_SIZE;
		if (pos.y <= 0)
			pos.y -= BLOCK_SIZE;
		(*curr)->SetGridPosition(sf::Vector2i(pos.x / BLOCK_SIZE, pos.y / BLOCK_SIZE));
		pos.x = pos.x - ((int)pos.x % (int)BLOCK_SIZE);
		pos.y = pos.y - ((int)pos.y % (int)BLOCK_SIZE);
		(*curr)->SetPosition(pos);
		map->AddElement(*curr);
	});
	mEditor->SetEventListener(mf::eEvent::RIGHT_CLICK, [map, win, position] {
		sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*win->GetRenderWindow()));
		pos += *position;
		if (pos.x <= 0)
			pos.x -= BLOCK_SIZE;
		if (pos.y <= 0)
			pos.y -= BLOCK_SIZE;
		map->RemoveElement(sf::Vector2i(pos.x / BLOCK_SIZE, pos.y / BLOCK_SIZE));
	});
}




void		EditorState::Init(Data *tData)
{
	mIsActive = true;
	mWindow->ShowCursor();
	mStateReturnAction = StateAction::POP;
	mData = tData;
	mSelectedElement = NULL;
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
		if (pos.x <= 0)
			pos.x -= BLOCK_SIZE;
		if (pos.y <= 0)
			pos.y -= BLOCK_SIZE;
		pos.x /= BLOCK_SIZE;
		pos.y /= BLOCK_SIZE;
		
		mPhantomSprite.setPosition((int)pos.x * BLOCK_SIZE, (int)pos.y * BLOCK_SIZE);
		sf::Texture		*texture = ResourceManager::LoadTexture(mSelectedElement->GetPath());
		mPhantomSprite.setTexture(*texture);
		mPhantomSprite.setScale(sf::Vector2f(BLOCK_SIZE / texture->getSize().x, BLOCK_SIZE / texture->getSize().y));
		mPhantomSprite.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
		mPhantomSprite.setColor(sf::Color(255, 255, 255, 100));
	}
	if (InputManager::IsActive(InputAction::MOVE_LEFT))
		mEditorPosition.x -= BLOCK_SIZE / 64.f;
	if (InputManager::IsActive(InputAction::MOVE_RIGHT))
		mEditorPosition.x += BLOCK_SIZE / 64.f;
	if (InputManager::IsActive(InputAction::MOVE_DOWN))
		mEditorPosition.y += BLOCK_SIZE / 64.f;
	if (InputManager::IsActive(InputAction::MOVE_UP))
		mEditorPosition.y -= BLOCK_SIZE / 64.f;
}

void		EditorState::Render()
{
	mWindow->Clear(sf::Color(100, 100, 100, 255));
	
	mf::GUI::Render();
	mView = *mEditor->GetView(mWindow->GetRenderWindow());
	mView.zoom(mZoom);
	mView.setCenter((mEditorPosition) + (mEditor->GetSize() / 2.f) + mEditor->GetPosition());
	mWindow->SetView(mView);
	mData->mMap.Render(mWindow);
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
	float	x = -((int)(mEditorPosition.x * 100.f) % (int)(BLOCK_SIZE * 100.f)) / 100.f;
	float	y = -((int)(mEditorPosition.y * 100.f) % (int)(BLOCK_SIZE * 100.f)) / 100.f;

	while (y < mWindow->GetSize().y)
	{
		mLine[0].position = sf::Vector2f(0, y);
		mLine[1].position = sf::Vector2f(mWindow->GetSize().x, y);
		mWindow->Draw(mLine, 2, sf::Lines);
		y += BLOCK_SIZE;
	}
	while (x < mWindow->GetSize().x)
	{
		mLine[0].position = sf::Vector2f(x, 0);
		mLine[1].position = sf::Vector2f(x, mWindow->GetSize().y);
		mWindow->Draw(mLine, 2, sf::Lines);
		x += BLOCK_SIZE;
	}
}