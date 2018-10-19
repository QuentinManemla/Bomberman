#ifndef FAILSTATE_HPP
# define FAILSTATE_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! Shows all the options for if you died in game
class FailState : public MenuParentState {
public:
	//! Constructor that takes ptr to GameEngine
	FailState( Engine & engine );
	~FailState( void );

private:
	void	_makeSelection( void );

};

#endif