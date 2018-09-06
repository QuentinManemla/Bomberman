#ifndef MENU_HPP
# define MENU_HPP

# include <iostream>
# include <vector>
# include "IState.hpp"
# include "MenuParentState.hpp"

class MenuState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	MenuState( Engine & engine );
	~MenuState( void );

private:
	void	_makeSelection( void ) override;

};

#endif