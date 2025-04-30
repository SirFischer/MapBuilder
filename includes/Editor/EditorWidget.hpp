#pragma once

#include "mfGUI.hpp"

class EditorWidget : public mf::Widget
{
private:
	EditorWidget(/* args */);
	
	/**
	 * Widget Components
	 **/
	
	mf::component::Background	mBackground;
	
	
	sf::View		mView;
	
public:
	~EditorWidget();
	static std::shared_ptr<EditorWidget>	Create();

	void					Render(sf::RenderWindow *tWindow);

	sf::View				*GetView(sf::RenderWindow *tWindow);

	void					SetPosition(float tX, float tY);
	void					SetPosition(sf::Vector2f tPos);
	void					SetSize(float tX, float tY);
	void					SetSize(sf::Vector2f tSize);
	void					SetEventListener(mf::eEvent tEvent, std::function<void()> tListener);
};

