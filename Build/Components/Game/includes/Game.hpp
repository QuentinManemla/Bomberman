#ifndef GAME_H
# define GAME_H

# include <iostream>
# include <unistd.h>

# include "../../../States/enumState.hpp" // hopefully cmake sorts this out
# include "../../Engine/includes/Engine.hpp"
# include "../../../States/IState/IState.hpp"
# include "../../../States/Intro/includes/Intro.hpp"
# include "../../../States/Menu/includes/Menu.hpp"
# include "../../../States/Play/includes/Play.hpp"
# include "../../../States/Credits/includes/Credits.hpp"
# include "../../../States/Quit/includes/Quit.hpp"

class Game {
public:
	Game( void );
	~Game( void );
	void	init();
	void	run();
protected:

private:
	void	_mainLoop();
	void	_switchState();
	
	eState	_state;
	Engine	_engine;

	IState	*_currentState; // type interface IState // set default on construction // possibly initialize everything on construction
};

#endif