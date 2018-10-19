#ifndef MENU_HPP
# define MENU_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//! Main menue state
class MenuState : public MenuParentState {
public:
	//! Constructor that takes ptr to GameEngine
	MenuState( Engine & engine );
	~MenuState( void );

private:
	void	_makeSelection( void );
};

#endif