#ifndef QUIT_HPP
# define QUIT_HPP

# include <iostream>
# include "IState.hpp"

class QuitState : public IState {
public:
	// constructor that takes ptr to GameEngine
	QuitState( void );
	~QuitState( void );

protected:

private:
	// ptr to GameEngine

};

#endif