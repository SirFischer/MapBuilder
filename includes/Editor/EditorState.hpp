#pragma once

#include "State.hpp"
#include "EditorWidget.hpp"

class EditorState : public State
{
private:
	EditorWidget	*mEditor;
	mf::List		*mOptions;
	mf::List		*mTextures;

	/**
	 * Options
	 **/
	
	mf::Slider		*mGridSizeSlider;

	/*********/

	sf::Vertex		mLine[2];
	float			mGridCellSize = 50.f;

	void			RenderGrid();

	void			InitGUI();
	void			InitOptions();
	void			InitTextures();
public:
	EditorState(Window *tWindow);
	~EditorState();

	void			Init(Data *tData);
	void			HandleEvents();
	void			Update();
	void			Render();
};

