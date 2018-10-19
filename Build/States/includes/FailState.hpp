#ifndef FAILSTATE_HPP
# define FAILSTATE_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! shows all the options for if you died in game
class FailState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	FailState( Engine & engine );
	~FailState( void );

private:
	void	_makeSelection( void );

};

#endif