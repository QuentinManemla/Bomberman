#ifndef FAILSTATE_HPP
# define FAILSTATE_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class FailState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	FailState( Engine & engine );
	~FailState( void );

private:
	void	_makeSelection( void );

};

#endif