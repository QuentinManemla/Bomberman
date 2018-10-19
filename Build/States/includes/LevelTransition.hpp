#ifndef LEVELTRANSITION_HPP
# define LEVELTRANSITION_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class LevelTransitionState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	LevelTransitionState( Engine & engine );
	LevelTransitionState(LevelTransitionState const & src);
	LevelTransitionState	&operator=(LevelTransitionState const &rhs);
	~LevelTransitionState( void );

private:
	void	_makeSelection( void );

};

#endif