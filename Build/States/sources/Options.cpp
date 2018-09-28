#include "../includes/Options.hpp"

OptionsState::OptionsState( Engine & engine ){
	this->_type = "Options";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrOptionsMenu[4] = {"Controls", "Fullscreen", "Resolution", "Volume"};
	this->_menu.insert(this->_menu.end(), std::begin(arrOptionsMenu), std::end(arrOptionsMenu));
}

OptionsState::~OptionsState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	OptionsState::_makeSelection( void){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	// update state depending on selection:
	if(this->_menuIndex == 1)
		this->_engine->state = FULLSCREEN;
	if (this->_menuIndex == 2) // test
		this->_engine->state = RESOLUTION; // test
	if (this->_menuIndex == 0)
		this->_engine->state = CONTROLS;
	/*if (this->_menuIndex == 0) // test
		this->_engine->state = PLAY; // test
	if (this->_menuIndex == 4) // test
		this->_engine->state = BACK; // test*/
}
