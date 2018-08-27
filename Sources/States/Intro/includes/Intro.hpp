#ifndef INTRO_HPP
# define INTRO_HPP

# include <iostream>
# include "IState.hpp"

class IntroState : public IState {
public:
	// constructor that takes ptr to GameEngine
	IntroState( void );
	~IntroState( void );

protected:

private:
	// ptr to GameEngine

};

#endif