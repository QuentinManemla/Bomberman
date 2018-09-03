#ifndef QUIT_HPP
# define QUIT_HPP

# include <iostream>
# include "../../IState/IState.hpp"

class QuitState : public IState {
public:
	// constructor that takes ptr to GameEngine
	QuitState( void );
	QuitState( Engine & engine );
	~QuitState( void );

	void update( eControls key );
	void render( void );
protected:

private:
	Engine	*_engine;
};

#endif