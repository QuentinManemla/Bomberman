#ifndef OPTIONSRESOLUTION_HPP
# define OPTIONSRESOLUTION_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class OptionsResolutionState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	OptionsResolutionState( Engine & engine );
	OptionsResolutionState(OptionsResolutionState const & src);
	OptionsResolutionState	&operator=(OptionsResolutionState const &rhs);
	~OptionsResolutionState( void );

private:
	void	_makeSelection( void );

};

#endif