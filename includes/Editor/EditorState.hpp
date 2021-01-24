#pragma once

#include "State.hpp"
#include "EditorWidget.hpp"

class EditorState : public State
{
private:
	EditorWidget	*mEditor;

	sf::CircleShape	circle;

public:
	EditorState(Window *tWindow);
	~EditorState();

	void		Init(Data *tData);
	void		HandleEvents();
	void		Update();
	void		Render();
};

