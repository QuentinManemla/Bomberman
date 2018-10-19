#ifndef MENU_HPP
# define MENU_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class MenuState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	MenuState( Engine & engine );
	MenuState(MenuState const & src);
	MenuState	&operator=(MenuState const &rhs);
	~MenuState( void );

private:
	void	_makeSelection( void );
};

#endif