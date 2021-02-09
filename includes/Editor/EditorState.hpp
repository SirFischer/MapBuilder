#pragma once

#include <filesystem>
#include <list>
#include <cstdlib>

#include "State.hpp"
#include "EditorWidget.hpp"
#include "Element.hpp"
#include "ResourceManager.hpp"

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
	std::list<Element>		mMapElements;
	sf::Sprite				mBlockSprite;

	/**
	 * Options
	 **/
	
	mf::Slider		*mGridSizeSlider;

	/*********/

	sf::Vertex		mLine[2];
	bool			mGridActive = true;
	float			mGridCellSize = 50.f;

	void			RenderGrid();
	void			RenderMap();

	void			InitGUI();
	void			InitBackButton();
	void			InitOptions();
	void			InitGridActivationButton();
	void			InitTextures();
	void			InitTextureLoader();
	void			InitElementEditor();
	void			InitElementPlacer();
public:
	EditorState(Window *tWindow);
	~EditorState();

	void			Init(Data *tData);
	void			HandleEvents();
	void			Update();
	void			Render();
	
	void			LoadTextures();
};

