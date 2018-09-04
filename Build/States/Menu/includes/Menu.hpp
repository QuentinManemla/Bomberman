#ifndef MENU_HPP
# define MENU_HPP

# include <iostream>
# include <vector>
# include "../../IState/IState.hpp"

class MenuState : public IState {
public:
	// constructor that takes ptr to GameEngine
	MenuState( void );
	MenuState( Engine & engine );
	~MenuState( void );

	void update( eControls key );
	void render( void );
protected:

private:
	void	_changeSelection( eControls key );
	void	_makeSelection( void );

	int							_menuIndex;
	int							_menuSize;
	std::vector<std::string>	_mainMenu;
	std::vector<std::string>	_optionsMenu;
	Engine						*_engine;
	int							_subState;
};

#endif