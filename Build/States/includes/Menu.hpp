#ifndef MENU_HPP
# define MENU_HPP

# include <iostream>
# include <array>
# include "IState.hpp"

class MenuState : public IState {
public:
	// constructor that takes ptr to GameEngine
	MenuState( void );
	MenuState( Engine & engine );
	~MenuState( void );

	std::string getType( void ); // debug


	void update( eControls key );
	void render( void );

	std::string type; // debug
protected:

private:
	void	_changeSelection( eControls key );
	void	_makeSelection( int _menuIndex );

	int							_menuIndex;
	int							_menuSize;
	std::array<std::string, 5>	_MainMenuOptions;
	Engine *_engine;
	//std::list<std::string>_MainMenuOptions;
};

#endif