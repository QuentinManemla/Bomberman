#ifndef MENU_HPP
# define MENU_HPP

# include <iostream>
# include "IState.hpp"

class MenuState : public IState {
public:
	// constructor that takes ptr to GameEngine
	MenuState( void );
	~MenuState( void );

protected:

private:
	// ptr to GameEngine

};

#endif