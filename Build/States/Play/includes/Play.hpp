#ifndef PLAY_HPP
# define PLAY_HPP

# include <iostream>
# include "../../IState/IState.hpp"

class PlayState : public IState {
public:
	// constructor that takes ptr to GameEngine
	PlayState( void );
	PlayState( Engine & engine );
	~PlayState( void );

	void update( eControls key );
	void render( void );
protected:

private:
	Engine *_engine;
};

#endif