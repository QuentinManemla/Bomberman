#ifndef LEVELTRANSITION_HPP
# define LEVELTRANSITION_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! Level transition state inhereting from MenuParentState
class LevelTransitionState : public MenuParentState {
public:
	//! Constructor that takes ptr to GameEngine
	LevelTransitionState( Engine & engine );
	~LevelTransitionState( void );

private:
	void	_makeSelection( void );

};

#endif