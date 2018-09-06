#include "../includes/Pause.hpp"

PauseState::PauseState( Engine & engine ){
	this->_type = "Pause";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrPauseMenu[3] = {"Resume", "Save and quit to menu", "Quit to menu"};
	this->_menu.insert(this->_menu.end(), std::begin(arrPauseMenu), std::end(arrPauseMenu));
}

PauseState::~PauseState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	PauseState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug

	// update state depending on selection:
	if (this->_menuIndex == 0) // test
		this->_engine->state = BACK; // test
	else if (this->_menuIndex == 2)
		this->_engine->state = BACK_TO_MAIN;
}