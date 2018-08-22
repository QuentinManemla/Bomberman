#ifndef GAME_H
# define GAME_H

# include "EntityManager.hpp"

# include <iostream>
# include <unistd.h>
# include <SFML/System.hpp>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

class Game {
public:
	Game( void );
	~Game( void );
	void	gameloop( void );
	int		getKey( void );
	void	draw( void );

protected:

private:
	EntityManager		*_EM;
	sf::RenderWindow	_win;

};

#endif