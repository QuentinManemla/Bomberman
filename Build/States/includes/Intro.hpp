#ifndef INTRO_HPP
# define INTRO_HPP

# include <iostream>
# include "IState.hpp"

class IntroState : public IState {
public:
	// constructor that takes ptr to GameEngine
	IntroState( void );
	IntroState( Engine & engine );
	~IntroState( void );

	std::string getType( void ); // debug


	void update( eControls key );
	void render( void );

	std::string type; // debug
protected:

private:
	Engine *_engine;
};

#endif