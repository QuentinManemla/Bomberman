#ifndef PLAY_HPP
# define PLAY_HPP

# include <iostream>
# include "../../IState/IState.hpp"

class PlayState : public IState {
public:
	// constructor that takes ptr to GameEngine
	PlayState( void );
	~PlayState( void );

	void update( void );
	void render( void );
protected:

private:
	// ptr to GameEngine

};

#endif