#ifndef CREDITS_HPP
# define CREDITS_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! State describing the credits inhereting from MenuParentState
class CreditsState : public MenuParentState {
public:
	//! Constructor that takes ptr to GameEngine
	CreditsState( Engine & engine );
	~CreditsState( void );

private:
	void	_makeSelection( void );

};

#endif