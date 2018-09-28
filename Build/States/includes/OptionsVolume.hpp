#ifndef OPTIONSVOLUME_HPP
# define OPTIONSVOLUME_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class OptionsVolumeState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	OptionsVolumeState( Engine & engine );
	~OptionsVolumeState( void );

private:
	void	_makeSelection( void );

};

#endif