#ifndef GAME_H
# define GAME_H

# include <iostream>
# include <unistd.h>
# include <stack>

# include "../../Engine/includes/Engine.hpp"

// state related includes
# include "../../../States/includes/enumState.hpp" // hopefully cmake sorts this out
# include "../../../States/includes/IState.hpp"
# include "../../../States/includes/Intro.hpp"
# include "../../../States/includes/Menu.hpp"
# include "../../../States/includes/Play.hpp"
# include "../../../States/includes/Credits.hpp"
# include "../../../States/includes/Quit.hpp"
# include "../../../States/includes/Options.hpp"
# include "../../../States/includes/Pause.hpp"
# include "../../../States/includes/OptionsResolution.hpp"
# include "../../../States/includes/OptionsFullScreen.hpp"

class Game {
public:
	Game( void );
	~Game( void );
	void	run();

protected:

private:
	void	_mainLoop( void );
	void	_switchState( void );
	void	_pushState( void );
	void	_popState( void );
	void	debugprintstack(); // debug
	
	Engine				_engine;
	std::stack<IState*>	_stateStack;
};

#endif