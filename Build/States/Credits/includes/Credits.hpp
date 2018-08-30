#ifndef CREDITS_HPP
# define CREDITS_HPP

# include <iostream>
# include "../../IState/IState.hpp"

class CreditsState : public IState {
public:
	// constructor that takes ptr to GameEngine
	CreditsState( void );
	CreditsState( Engine & engine );
	~CreditsState( void );

	void update( eControls key );
	void render( void );
protected:

private:
	Engine	*_engine;
};

#endif