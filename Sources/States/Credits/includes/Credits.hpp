#ifndef CREDITS_HPP
# define CREDITS_HPP

# include <iostream>
# include "IState.hpp"

class CreditsState : public IState {
public:
	// constructor that takes ptr to GameEngine
	CreditsState( void );
	~CreditsState( void );

protected:

private:
	// ptr to GameEngine

};

#endif