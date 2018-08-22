#ifndef GAME_H
# define GAME_H

# include <iostream>
# include <unistd.h>

class Game {
public:
	Game( void );
	~Game( void );
	void	init();

protected:

private:
	void	_mainLoop();
	void	_switchState();

	IState	*_currentState; // type interface IState // set default on construction // possibly initialize everything on construction
};

#endif