#ifndef PLAY_HPP
# define PLAY_HPP

# include <iostream>
# include "IState.hpp"

class PlayState : public IState {
public:
	// constructor that takes ptr to GameEngine
	PlayState( void );
	PlayState( Engine & engine );
	~PlayState( void );

		std::string getType( void ); // debug


	void update( eControls key );
	void render( void );

	std::string type; // debug
protected:

private:
	Engine *_engine;
};

#endif