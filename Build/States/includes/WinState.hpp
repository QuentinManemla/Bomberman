#ifndef WIN_HPP
# define WIN_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! win menu state
class WinState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	WinState( Engine & engine );
	~WinState( void );

private:
	void	_makeSelection( void );

};

#endif