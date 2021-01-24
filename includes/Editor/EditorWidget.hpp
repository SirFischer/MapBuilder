#pragma once

#include "mfGUI.hpp"

class EditorWidget : public mf::Widget
{
private:
	EditorWidget(/* args */);
	~EditorWidget();

	/**
	 * Widget Components
	 **/

	mf::component::Background	mBackground;


	sf::View		mView;

public:
	static EditorWidget*	Create();

	void					Render(sf::RenderWindow *tWindow);

	sf::View				*GetView(sf::RenderWindow *tWindow);

	EditorWidget			*SetPosition(float tX, float tY);
	EditorWidget			*SetPosition(sf::Vector2f tPos);
	EditorWidget			*SetSize(float tX, float tY);
	EditorWidget			*SetSize(sf::Vector2f tSize);
};

