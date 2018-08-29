#include "../includes/Menu.hpp"

MenuState::MenuState( void ){
	std::cout << "Menu constructed" << std::endl; // debug
	this->_MainMenuOptions[0] = "New game";
	this->_MainMenuOptions[1] = "Load game";
	this->_MainMenuOptions[2] = "Options";
	this->_MainMenuOptions[3] = "Credits";
	this->_MainMenuOptions[4] = "Quit";
	this->_menuSize = this->_MainMenuOptions.size();
	this->_menuIndex = 0;
}

MenuState::~MenuState( void ){
	std::cout << "Menu destructed" << std::endl; // debug
}

void MenuState::update( void ){
	std::cout << "Menu update" << std::endl; // debug
}

void MenuState::render( Engine & engine ){
	// engine.renderMenu() // specialized menu rendering engine
	std::cout << this->_menuIndex << std::endl;
	// END FAKE renderMenu()
	engine.render();
	std::cout << "Menu render" << std::endl; // debug

}

void	MenuState::_changeSelection( eControls key){
	switch (key){
		case UP:
			this->_menuIndex--;
			break;
		case DOWN:
			this->_menuIndex++;
			break;
		case ENTER:
			this->_makeSelection(this->_menuIndex);
			break;
		default:
			break;
	};
}

void	MenuState::_makeSelection( int _menuIndex ){

}