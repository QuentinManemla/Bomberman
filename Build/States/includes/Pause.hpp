#ifndef PAUSE_HPP
# define PAUSE_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! pause menu state
class PauseState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	PauseState( Engine & engine );
	~PauseState( void );

private:
	void	_makeSelection( void );

};

#endif