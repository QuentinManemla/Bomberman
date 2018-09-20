#include "../includes/OptionsResolution.hpp"

OptionsResolutionState::OptionsResolutionState( Engine & engine ) {
	this->_type = "Resolution";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrMainMenu[3] = {"800 x 600 4:3", "1024 x 768 4:3", "1920 x 1080 16:9"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
}

OptionsResolutionState::~OptionsResolutionState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	OptionsResolutionState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	if (this->_menuIndex == 0)
		this->_engine->setResolution(800, 600);
	if (this->_menuIndex == 1)
		this->_engine->setResolution(1024, 768);
	if (this->_menuIndex == 2)
		this->_engine->setResolution(1920, 1080);
}