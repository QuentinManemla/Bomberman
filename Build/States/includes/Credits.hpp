#ifndef CREDITS_HPP
# define CREDITS_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class CreditsState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	CreditsState( Engine & engine );
	~CreditsState( void );

private:
	void	_makeSelection( void );

};

#endif