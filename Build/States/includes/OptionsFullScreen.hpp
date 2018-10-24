#ifndef OPTIONFULLSCREEN_HPP
# define OPTIONFULLSCREEN_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class OptionsFullScreenState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	OptionsFullScreenState( Engine & engine );
	~OptionsFullScreenState( void );

private:
	void	_makeSelection( void );

};

#endif