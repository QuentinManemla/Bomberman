#ifndef OPTIONCONTROLS_HPP
# define OPTIONCONTROLS_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! Control option state
class OptionsControlsState : public MenuParentState {
public:
	//! Constructor that takes ptr to GameEngine
	OptionsControlsState( Engine & engine );
	~OptionsControlsState( void );

private:
	void	_makeSelection( void );

};

#endif