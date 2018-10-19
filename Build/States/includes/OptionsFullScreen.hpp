#ifndef OPTIONFULLSCREEN_HPP
# define OPTIONFULLSCREEN_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class OptionsFullScreenState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	OptionsFullScreenState( Engine & engine );
	OptionsFullScreenState(OptionsFullScreenState const & src);
	OptionsFullScreenState	&operator=(OptionsFullScreenState const &rhs);
	~OptionsFullScreenState( void );

private:
	void	_makeSelection( void );

};

#endif