#include "../includes/LoadGame.hpp"

LoadGameState::LoadGameState( Engine & engine ) {
	this->_type = "Load Game";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::ifstream f(".save/save.save");
	if (f.good()) {
		std::string arrMainMenu[1] = {"save/save.save"};
		this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
	} else {
		std::string arrMainMenu[1] = {"No Save Games Found"};
		this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
	}
}

LoadGameState::LoadGameState(LoadGameState const & src) {}

LoadGameState	&LoadGameState::operator=(LoadGameState const &rhs) {}

LoadGameState::~LoadGameState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void	LoadGameState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug

	std::ifstream f(".save/save.save");
	if (f.good()) {
		if (this->_menuIndex == 0) {
			this->_engine->loadGame();
			this->_engine->state = PLAYLOADGAME;
		}
	}
}