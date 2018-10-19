#ifndef OPTIONS_HPP
# define OPTIONS_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class OptionsState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	OptionsState( Engine & engine );
	OptionsState(OptionsState const & src);
	OptionsState	&operator=(OptionsState const &rhs);
	~OptionsState( void );

private:
	void	_makeSelection( void );
	
};

#endif