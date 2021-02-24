#pragma once

#include <filesystem>
#include <list>
#include <cstdlib>
#include <math.h>

#include "State.hpp"
#include "EditorWidget.hpp"
#include "Element.hpp"
#include "ResourceManager.hpp"
#include "InputManager.hpp"

#define DEFAULT_RESOURCES "assets/defaultResources"

class EditorState : public State
{
private:
	EditorWidget			*mEditor;
	mf::List				*mOptions;
	mf::List				*mTextures;
	mf::List				*mElementEditor;
	Element					*mSelectedElement = NULL;
	Element					*mPreviousSelectedElement = NULL;
	std::vector<Element>	mElementList;
	sf::Sprite				mPhantomSprite;

	sf::Vector2f			mEditorPosition = sf::Vector2f(0, 0);
	sf::View				mView;
	float					mZoom = 1.f;

	/**
	 * Options
	 **/
	

	/*********/

	sf::Vertex		mLine[2];
	bool			mGridActive = true;

	void			RenderGrid();

	void			InitGUI();
	void			InitBackButton();
	void			InitSaveButton();
	void			InitSettingsButton();
	void			InitOptions();
	void			InitGridActivationButton();
	void			InitTextures();
	void			InitTextureLoader();
	void			InitElementEditor();
	void			InitElementPlacer();
	void			LoadTexturesFromFolder(std::string tPath);
public:
	EditorState(Window *tWindow);
	~EditorState();

	void			Init(Data *tData);
	void			HandleEvents();
	void			Update();
	void			Render();
	
	void			LoadTextures();
};

