#ifndef MENU_HPP
# define MENU_HPP

# include <iostream>
# include <array>
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
	void	_changeSelection( eControls key );
	void	_makeSelection( int _menuIndex );

	int						_menuIndex;
	int						_menuSize;
	std::array<std::string, 5>	_MainMenuOptions;
	//std::list<std::string>_MainMenuOptions;
};

#endif