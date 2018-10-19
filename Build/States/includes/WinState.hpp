#ifndef WIN_HPP
# define WIN_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class WinState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	WinState( Engine & engine );
	WinState(WinState const & src);
	WinState	&operator=(WinState const &rhs);
	~WinState( void );

private:
	void	_makeSelection( void );

};

#endif