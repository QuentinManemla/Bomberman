#include "../includes/OptionsResolution.hpp"

OptionsResolutionState::OptionsResolutionState( Engine & engine ) {
	this->_type = "Resolution";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrMainMenu[2] = {"800 x 600", "1024 x 768"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
}

OptionsResolutionState::~OptionsResolutionState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	OptionsResolutionState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	// update state depending on selection:
	/*
	if (this->_menuIndex == 0) 
		//do this 
	if (this->_menuIndex == 2)
		//do this
	*/
}