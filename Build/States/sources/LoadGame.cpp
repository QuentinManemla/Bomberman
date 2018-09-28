#include "../includes/LoadGame.hpp"

LoadGameState::LoadGameState( Engine & engine ) {
	this->_type = "Load Game";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrMainMenu[1] = {"./save/save.save"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));


}

LoadGameState::~LoadGameState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	LoadGameState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug

	if (this->_menuIndex == 0) {
		this->_engine->loadGame();
	}
}