#include "../includes/Credits.hpp"

CreditsState::CreditsState( Engine & engine ) {
	this->_type = "Credits";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;
	this->_engine->_SoundEngine.playSoundSource(this->_engine->_SoundEngine._Credits, true);

	std::string arrMainMenu[7] = {"Graphics Engine Design - Quentin",
	"Game Engine Design - Brenton", "Menu Engine - Brenton & Quentin",
	"State Engine - Brenton & Quentin (Mainly Brenton)","Sound Engine Design - Quentin",
	"Key Bindings & Controls - YenHo", "Compilation Architect - Jerome" };
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));


}

CreditsState::~CreditsState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
	this->_engine->_SoundEngine.stopSound();
}

void	CreditsState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
}