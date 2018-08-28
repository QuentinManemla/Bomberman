#ifndef MENU_HPP
# define MENU_HPP

# include <iostream>
# include <list>
# include "../../IState/IState.hpp"

class MenuState : public IState {
public:
	// constructor that takes ptr to GameEngine
	MenuState( void );
	~MenuState( void );

	void update( void );
	void render( Engine	&engine );
protected:

private:
	std::list<std::string>_MainMenuOptions;
};

#endif