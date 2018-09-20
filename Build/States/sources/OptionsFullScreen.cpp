#include "../includes/OptionsFullScreen.hpp"

OptionsFullScreenState::OptionsFullScreenState( Engine & engine ) {
	this->_type = "Resolution";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrMainMenu[3] = {"On", "Off"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
}

OptionsFullScreenState::~OptionsFullScreenState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	OptionsFullScreenState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	if (this->_menuIndex == 0)
		this->_engine->setFullScreen();
	if (this->_menuIndex == 1)
		this->_engine->setWindowed();
}