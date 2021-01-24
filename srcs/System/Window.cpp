#include "Window.hpp"

Window::Window(/* args */)
{
	Create();
}

Window::~Window()
{
}


void	Window::Create()
{
	mWindow.create(mMode, mTitle, (mFullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
	mf::GUI::Init(&mWindow);
}

void	Window::Destroy()
{
	mWindow.close();
}

void	Window::Draw(sf::Drawable &tDrawable)
{
	mWindow.draw(tDrawable);
}

void	Window::Draw(const sf::Vertex *tVertices, std::size_t tVertexCount, sf::PrimitiveType tPrimitiveType)
{
	mWindow.draw(tVertices, tVertexCount, tPrimitiveType);
}

void	Window::Clear()
{
	mWindow.clear();
}

void	Window::Clear(sf::Color tColor)
{
	mWindow.clear(tColor);
}

void	Window::Render()
{
	mWindow.display();
}

bool	Window::HandleEvent(sf::Event &tEvent)
{
	return (mWindow.pollEvent(tEvent));
}

void	Window::ToggleFullscreen()
{
	mFullscreen = !mFullscreen;
	Destroy();
	Create();
}

void	Window::ChangeResolution(int tWidth, int tHeight)
{
	mMode = sf::VideoMode(tWidth, tHeight);
	Destroy();
	Create();
}

void	Window::HideCursor()
{
	mWindow.setMouseCursorVisible(false);
}

void	Window::ShowCursor()
{
	mWindow.setMouseCursorVisible(true);
}

/**
 * View
 */
void	Window::ResetView(bool tResize)
{
	if (tResize)
		mWindow.setView(sf::View(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / 2), sf::Vector2f(mWindow.getSize())));
	else
		mWindow.setView(mWindow.getDefaultView());
}

/**
 * Setters
 **/

void	Window::SetView(sf::View tView)
{
	mWindow.setView(tView);
}

