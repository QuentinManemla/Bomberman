#include "../includes/OptionsVolume.hpp"

OptionsVolumeState::OptionsVolumeState( Engine & engine ) {
	this->_type = "Volume";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrMainMenu[4] = {"High", "Meduim", "Low", "Mute"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
}

OptionsVolumeState::~OptionsVolumeState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	OptionsVolumeState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	if (this->_menuIndex == 0)
		this->_engine->setVolume(1.0f);
	if (this->_menuIndex == 1)
		this->_engine->setVolume(0.5f);
	if (this->_menuIndex == 2)
		this->_engine->setVolume(0.1f);
	if (this->_menuIndex == 3)
		this->_engine->setVolume(0.0f);
}