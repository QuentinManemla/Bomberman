#ifndef OPTIONS_HPP
# define OPTIONS_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! Options menu state
class OptionsState : public MenuParentState {
public:
	//! Constructor that takes ptr to GameEngine
	OptionsState( Engine & engine );
	~OptionsState( void );

private:
	void	_makeSelection( void );
	
};

#endif