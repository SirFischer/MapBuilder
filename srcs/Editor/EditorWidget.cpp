#include "EditorWidget.hpp"

EditorWidget::EditorWidget(/* args */)
:mBackground(&mTransform.mPosition, &mTransform.mSize)
{
	mBackground.SetBackground(sf::Color::Black);
	SetSize(70, 85);
	SetPositionPercentage(true, true);
	SetSizePercentage(true, true);
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
	mView.reset(sf::FloatRect(mTransform.mPosition.x, mTransform.mPosition.y, mTransform.mSize.x, mTransform.mSize.y));
	return (this);
}


EditorWidget	*EditorWidget::SetPosition(sf::Vector2f tPos)
{
	Widget::SetPosition(tPos);
	mView.reset(sf::FloatRect(mTransform.mPosition.x, mTransform.mPosition.y, mTransform.mSize.x, mTransform.mSize.y));
	return (this);
}

EditorWidget	*EditorWidget::SetSize(float tX, float tY)
{
	Widget::SetSize(tX, tY);
	mView.reset(sf::FloatRect(mTransform.mPosition.x, mTransform.mPosition.y, mTransform.mSize.x, mTransform.mSize.y));
	return (this);
}

EditorWidget	*EditorWidget::SetSize(sf::Vector2f tSize)
{
	Widget::SetSize(tSize);
	mView.reset(sf::FloatRect(mTransform.mPosition.x, mTransform.mPosition.y, mTransform.mSize.x, mTransform.mSize.y));
	return (this);
}

sf::View		*EditorWidget::GetView(sf::RenderWindow *tWindow)
{
	mView.setViewport(sf::FloatRect(mTransform.mPosition.x / (float)tWindow->getSize().x, mTransform.mPosition.y / (float)tWindow->getSize().y, mTransform.mSize.x / (float)tWindow->getSize().x, mTransform.mSize.y / (float)tWindow->getSize().y));
	return (&mView);
}

EditorWidget	*EditorWidget::SetEventListener(mf::eEvent tEvent, std::function<void()> tListener)
{
	mEventManager.AddEventListener(tEvent, tListener);
	return (this);
}
