#include "Core.hpp"

int main( void )
{
	Window		window;

	window.GetRenderWindow()->setFramerateLimit(60);

	StateManager	stateManager(&window);

	stateManager.Run();

	return (0);
}