#include "EditorWidget.hpp"

EditorWidget::EditorWidget(/* args */)
:mBackground(&mPosition, &mSize)
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

std::shared_ptr<EditorWidget>	EditorWidget::Create()
{
	std::shared_ptr<EditorWidget> tmp = std::shared_ptr<EditorWidget>(new EditorWidget());
	return (tmp);
}

void			EditorWidget::Render(sf::RenderWindow *tWindow)
{
	mBackground.Draw(tWindow);
	Widget::Render(tWindow);
}

void	EditorWidget::SetPosition(float tX, float tY)
{
	Widget::SetPosition(tX, tY);
	mView.reset(sf::FloatRect(mPosition.x, mPosition.y, mSize.x, mSize.y));
}


void	EditorWidget::SetPosition(sf::Vector2f tPos)
{
	Widget::SetPosition(tPos);
	mView.reset(sf::FloatRect(mPosition.x, mPosition.y, mSize.x, mSize.y));
}

void	EditorWidget::SetSize(float tX, float tY)
{
	Widget::SetSize(tX, tY);
	mView.reset(sf::FloatRect(mPosition.x, mPosition.y, mSize.x, mSize.y));
}

void	EditorWidget::SetSize(sf::Vector2f tSize)
{
	Widget::SetSize(tSize);
	mView.reset(sf::FloatRect(mPosition.x, mPosition.y, mSize.x, mSize.y));
	
}

sf::View		*EditorWidget::GetView(sf::RenderWindow *tWindow)
{
	mView.setViewport(sf::FloatRect(mPosition.x / (float)tWindow->getSize().x, mPosition.y / (float)tWindow->getSize().y, mSize.x / (float)tWindow->getSize().x, mSize.y / (float)tWindow->getSize().y));
	return (&mView);
}

void	EditorWidget::SetEventListener(mf::eEvent tEvent, std::function<void()> tListener)
{
	mEventManager.AddEventListener(tEvent, tListener);
	
}
