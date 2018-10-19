#ifndef OPTIONSRESOLUTION_HPP
# define OPTIONSRESOLUTION_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! resolution option state
class OptionsResolutionState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	OptionsResolutionState( Engine & engine );
	~OptionsResolutionState( void );

private:
	void	_makeSelection( void );

};

#endif