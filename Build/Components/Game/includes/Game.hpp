#ifndef GAME_H
# define GAME_H

# include <iostream>
# include <unistd.h>
# include <stack>

# include "../../Engine/includes/Engine.hpp"

// state related includes
# include "../../../States/includes/enumState.hpp"
# include "../../../States/includes/IState.hpp"
# include "../../../States/includes/Intro.hpp"
# include "../../../States/includes/Menu.hpp"
# include "../../../States/includes/Play.hpp"
# include "../../../States/includes/Credits.hpp"
# include "../../../States/includes/Quit.hpp"
# include "../../../States/includes/Options.hpp"
# include "../../../States/includes/Pause.hpp"
# include "../../../States/includes/OptionsControls.hpp"
# include "../../../States/includes/OptionsResolution.hpp"
# include "../../../States/includes/OptionsFullScreen.hpp"
# include "../../../States/includes/PauseSaveQuit.hpp"
# include "../../../States/includes/OptionsVolume.hpp"
# include "../../../States/includes/LevelTransition.hpp"
# include "../../../States/includes/LoadGame.hpp"
# include "../../../States/includes/FailState.hpp"
# include "../../../States/includes/WinState.hpp"

//! The first object that runs which starts everything
class Game {
public:
	/*!
	 * inits the Engine
	 * and adds the quit menue and intro state to the state list.
	 */
	Game( void );
	~Game( void );
	//! starts the game loop which does
	/*! 
	 using IState
	 \arg update updates the states depending on key press
	 \arg render draws everything to the screen
	 \n \n
	 \arg change changes the state if need be
	 \arg FPSManager manages the fps using Engine
	 */
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