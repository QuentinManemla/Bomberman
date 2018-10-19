#ifndef LOADGAME_HPP
# define LOADGAME_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class LoadGameState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	LoadGameState( Engine & engine );
	LoadGameState(LoadGameState const & src);
	LoadGameState	&operator=(LoadGameState const &rhs);
	~LoadGameState( void );

private:
	void	_makeSelection( void );

};

#endif