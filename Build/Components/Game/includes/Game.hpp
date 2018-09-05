#ifndef GAME_H
# define GAME_H

# include <iostream>
# include <unistd.h>
# include <stack>

# include "../../../States/includes/enumState.hpp" // hopefully cmake sorts this out
# include "../../Engine/includes/Engine.hpp"
# include "../../../States/includes/IState.hpp"
# include "../../../States/includes/Intro.hpp"
# include "../../../States/includes/Menu.hpp"
# include "../../../States/includes/Play.hpp"
# include "../../../States/includes/Credits.hpp"
# include "../../../States/includes/Quit.hpp"

class Game {
public:
	Game( void );
	~Game( void );
	void	init();
	void	run();

protected:

private:
	void	_mainLoop( void );
	void	_switchState( void );
	void	_pushState( void );
	void	_popState( void );
	void	debugprintstack(); // debug
	
	// eState	_state; moved to engine
	Engine				_engine;
	std::stack<IState*>	_stateStack;

	IState				*_currentState; // type interface IState // set default on construction // possibly initialize everything on construction
};

#endif