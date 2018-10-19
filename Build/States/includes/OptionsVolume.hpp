#ifndef OPTIONSVOLUME_HPP
# define OPTIONSVOLUME_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! volume option menu state
class OptionsVolumeState : public MenuParentState {
public:
	//! Constructor that takes ptr to GameEngine
	OptionsVolumeState( Engine & engine );
	~OptionsVolumeState( void );

private:
	void	_makeSelection( void );

};

#endif