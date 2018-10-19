#ifndef OPTIONSRESOLUTION_HPP
# define OPTIONSRESOLUTION_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! Resolution option state
class OptionsResolutionState : public MenuParentState {
public:
	//! Constructor that takes ptr to GameEngine
	OptionsResolutionState( Engine & engine );
	~OptionsResolutionState( void );

private:
	void	_makeSelection( void );

};

#endif