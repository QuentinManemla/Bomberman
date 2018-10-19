#ifndef LOADGAME_HPP
# define LOADGAME_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! load game state
class LoadGameState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	LoadGameState( Engine & engine );
	~LoadGameState( void );

private:
	void	_makeSelection( void );

};

#endif