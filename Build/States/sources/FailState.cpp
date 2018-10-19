#include "../includes/FailState.hpp"

FailState::FailState( Engine & engine ) {
	this->_type = "You Failed";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrMainMenu[2] = {"Restart Level", "Quit to Main Menu"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));


}

FailState::FailState(FailState const & src) {}

FailState	&FailState::operator=(FailState const &rhs) {}

FailState::~FailState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	FailState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug

	if (this->_menuIndex == 0) {
		this->_engine->state = RESTARTLEVEL;
	} else if (this->_menuIndex == 1) {
		this->_engine->state = BACK_TO_MAIN;
	}
}