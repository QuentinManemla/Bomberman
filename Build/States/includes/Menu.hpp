#ifndef MENU_HPP
# define MENU_HPP

# include <iostream>
# include <vector>
# include "IState.hpp"
# include "MenuParentState.hpp"

class MenuState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	MenuState( void );
	MenuState( Engine & engine );
	~MenuState( void );

	void	_makeSelection( void ) override;
};

#endif