#include "../includes/OptionsControls.hpp"

OptionsControlsState::OptionsControlsState( Engine & engine ) {
	this->_type = "Controls";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrMainMenu[2] = {"wasd", "arrowkeys"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
}

OptionsControlsState::OptionsControlsState(OptionsControlsState const & src) {}

OptionsControlsState	&OptionsControlsState::operator=(OptionsControlsState const &rhs) {}

OptionsControlsState::~OptionsControlsState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	OptionsControlsState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	if (this->_menuIndex == 1)
		this->_engine->controlChange(0);
	if (this->_menuIndex == 0)
		this->_engine->controlChange(1);
}