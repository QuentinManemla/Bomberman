#ifndef PAUSE_HPP
# define PAUSE_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class PauseState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	PauseState( Engine & engine );
	PauseState(PauseState const & src);
	PauseState	&operator=(PauseState const &rhs);
	~PauseState( void );

private:
	void	_makeSelection( void );

};

#endif