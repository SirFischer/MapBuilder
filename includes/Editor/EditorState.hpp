#pragma once

#include "State.hpp"

class EditorState : public State
{
private:
	/* data */
	
public:
	EditorState(Window *tWindow);
	~EditorState();

	void		Init();
	void		HandleEvents();
	void		Update();
	void		Render();
};

