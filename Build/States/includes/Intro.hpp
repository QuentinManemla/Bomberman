#ifndef INTRO_HPP
# define INTRO_HPP

# include <iostream>
# include "IState.hpp"

//! intro state
class IntroState : public IState {
public:
	//! constructor that takes ptr to GameEngine
	IntroState( void );
	IntroState( Engine & engine );
	~IntroState( void );

	std::string		getType( void ); // debug
	//! takes in a key, pass the intro and onto the main game menu
	void 			update( eControls key );
	//! rendering the intro of the game
	void 			render( void );

protected:

private:
	Engine			*_engine;
	std::string		_type; // debug
	
};

#endif