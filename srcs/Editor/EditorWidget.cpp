#include "EditorWidget.hpp"

EditorWidget::EditorWidget(/* args */)
:mBackground(&mPos, &mSize)
{
	mBackground.SetBackground(sf::Color::Black);
	SetSize(70, 85);
	SetPositionPercentage(true);
	SetSizePercentage(true);
	SetPosition(2, 5);
}

EditorWidget::~EditorWidget()
{
}

EditorWidget*	EditorWidget::Create()
{
	EditorWidget *tmp = new EditorWidget();
	return (tmp);
}

void			EditorWidget::Render(sf::RenderWindow *tWindow)
{
	mBackground.Draw(tWindow);
	Widget::Render(tWindow);
}

EditorWidget	*EditorWidget::SetPosition(float tX, float tY)
{
	Widget::SetPosition(tX, tY);
	mView.reset(sf::FloatRect(mPos.x, mPos.y, mSize.x, mSize.y));
	return (this);
}


EditorWidget	*EditorWidget::SetPosition(sf::Vector2f tPos)
{
	Widget::SetPosition(tPos);
	mView.reset(sf::FloatRect(mPos.x, mPos.y, mSize.x, mSize.y));
	return (this);
}

EditorWidget	*EditorWidget::SetSize(float tX, float tY)
{
	Widget::SetSize(tX, tY);
	mView.reset(sf::FloatRect(mPos.x, mPos.y, mSize.x, mSize.y));
	return (this);
}

EditorWidget	*EditorWidget::SetSize(sf::Vector2f tSize)
{
	Widget::SetSize(tSize);
	mView.reset(sf::FloatRect(mPos.x, mPos.y, mSize.x, mSize.y));
	return (this);
}

sf::View		*EditorWidget::GetView(sf::RenderWindow *tWindow)
{
	mView.setViewport(sf::FloatRect(mPos.x / (float)tWindow->getSize().x, mPos.y / (float)tWindow->getSize().y, mSize.x / (float)tWindow->getSize().x, mSize.y / (float)tWindow->getSize().y));
	return (&mView);
}

EditorWidget	*EditorWidget::SetEventListener(mf::eEvent tEvent, std::function<void()> tListener)
{
	mEventManager.AddEventListener(tEvent, tListener);
	return (this);
}
