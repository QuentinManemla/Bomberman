#include "../includes/PauseSaveQuit.hpp"

SaveQuitState::SaveQuitState( Engine & engine ) {
	this->_type = "Are you Sure ?";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;


	std::string arrMainMenu[3] = {"Yes", "No"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
}

SaveQuitState::~SaveQuitState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	SaveQuitState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	if (this->_menuIndex == 0) {
		this->_engine->saveGame();
		this->_engine->state = BACK_TO_MAIN;
	}
	if (this->_menuIndex == 1){
		this->_engine->state = BACK_TO_MAIN;
	}
}