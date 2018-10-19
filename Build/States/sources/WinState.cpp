#include "../includes/WinState.hpp"

WinState::WinState( Engine & engine ) {
	this->_type = "Sucess";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrMainMenu[3] = {"Continue","Save","Return to Main Menu"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
}

WinState::WinState(WinState const & src) {}

WinState	&WinState::operator=(WinState const &rhs) {}

WinState::~WinState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	WinState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug

	if (this->_menuIndex == 0) {
		this->_engine->state = CONTINUE;
	}
	else if (this->_menuIndex == 1) {
		this->_engine->saveGame();
	}
	else if (this->_menuIndex == 2){
		this->_engine->state = BACK_TO_MAIN;
	}

}