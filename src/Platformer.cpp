#include "Game.h"
#include <iostream>
int main()
{
	srand(static_cast<unsigned>(time(0)));
	sf::RenderWindow window;
	window.create(sf::VideoMode(1024, 1080), "Game 4", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	sf::Clock clock;
	Game game(window);


	while (game.getWindow().isOpen())
	{
		sf::Time dt = clock.restart();
		game.update(dt.asSeconds());
		game.render(dt.asSeconds());
	}

	//End of application
	return 0;
}