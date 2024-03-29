#ifndef OPTIONCONTROLS_HPP
# define OPTIONCONTROLS_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class OptionsControlsState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	OptionsControlsState( Engine & engine );
	~OptionsControlsState( void );

private:
	void	_makeSelection( void );

};

#endif