#ifndef INTRO_HPP
# define INTRO_HPP

# include <iostream>
# include "../../IState/IState.hpp"

class IntroState : public IState {
public:
	// constructor that takes ptr to GameEngine
	IntroState( void );
	IntroState( Engine & engine );
	~IntroState( void );

	void update( eControls key );
	void render( void );
protected:

private:
	Engine *_engine;
};

#endif