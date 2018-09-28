#include "../includes/Menu.hpp"

MenuState::MenuState( Engine & engine ) {
	this->_type = "Menu";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrMainMenu[5] = {"New game", "Load game", "Options", "Credits", "Quit"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
}

MenuState::~MenuState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	MenuState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	// update state depending on selection:
	if (this->_menuIndex == 0) // test
		this->_engine->state = PLAY; // test
	if (this->_menuIndex == 1)
		this->_engine->state = LOADGAME;
	if (this->_menuIndex == 2) // test
		this->_engine->state = OPTIONS; // test
	if (this->_menuIndex == 4) // test
		this->_engine->state = BACK; // test
}