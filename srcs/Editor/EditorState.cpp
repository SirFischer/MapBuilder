#include "EditorState.hpp"
#include "Components.hpp"

// Helper function to try loading texture from multiple locations
sf::Texture* TryLoadTextureEditor(const std::string& texturePath, const std::string& profileAssetsPath = "") {
	sf::Texture* texture = nullptr;
	
	std::filesystem::path textureFile(texturePath);
	std::string fileName = textureFile.filename().string();
	
	texture = ResourceManager::LoadTexture(texturePath);
	if (texture) return texture;
	
	std::string defaultPath = "assets/defaultResources/" + fileName;
	texture = ResourceManager::LoadTexture(defaultPath);
	if (texture) return texture;
	
	if (!profileAssetsPath.empty()) {
		std::string profilePath = profileAssetsPath + "/" + fileName;
		texture = ResourceManager::LoadTexture(profilePath);
		if (texture) return texture;
	}
	
	return nullptr;
}

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
	mTextures->SetSize(95, 40);
	mTextures->SetSizePercentage(true, true);
	mTextures->SetContentOffset(sf::Vector2f(10, 5));
	mTextures->GetBackground()->SetBackground(sf::Color(130, 130, 130));
	mTextures->SetItemDirection(mf::eDirection::HORIZONTAL);
	mTextures->SetContentOverflow(mf::List::eOverflow::WRAP);
	mTextures->GetBackground()->SetOutlineColor(sf::Color::Black);
	mTextures->GetBackground()->SetOutlineThickness(1.f);
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
		auto texture = TryLoadTextureEditor(mElementList.back().GetPath(), mData->mProfile.GetAssetsPath());
		auto btn = Components::CreateButton("", sf::Vector2f(50, 50), sf::Vector2f(0, 0), [this, entry] {
			mSelectedElement = &mElementList.back();
			mPhantomSprite.setTexture(*TryLoadTextureEditor(mSelectedElement->GetPath(), mData->mProfile.GetAssetsPath()));
		});
		btn->GetBackground()->SetBackground(*texture);
		btn->AddEventListener(mf::eEvent::ENTERED, [btn] {
			btn->GetBackground()->SetOutlineThickness(1);
		});
		btn->AddEventListener(mf::eEvent::EXITED, [btn] {
			btn->GetBackground()->SetOutlineThickness(0);
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
		auto img = mf::Image::Create();
		img->SetImage(mSelectedElement->GetPath());
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
		sf::Texture		*texture = TryLoadTextureEditor(mSelectedElement->GetPath(), mData->mProfile.GetAssetsPath());
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
	mData->mMap.Render(mWindow, mData->mProfile.GetAssetsPath());
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