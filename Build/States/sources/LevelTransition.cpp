# include "../includes/LevelTransition.hpp"

LevelTransitionState::LevelTransitionState( Engine & engine ) {
	this->_engine = &engine;

	if (this->_engine->_Save.success)
		this->_type = "You Win !";
	else
		this->_type = "You Lose !";
	this->_menuIndex = 0;

	std::string arrMainMenu[3] = {"Continue", "Restart Level", "Quit to Menu"};
	this->_menu.insert(this->_menu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
}

LevelTransitionState::LevelTransitionState(LevelTransitionState const & src) {}

LevelTransitionState	&LevelTransitionState::operator=(LevelTransitionState const &rhs) {}

LevelTransitionState::~LevelTransitionState( void ) { return ; }

void	LevelTransitionState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	// if (this->_menuIndex == 0)
	// 	// Do SOMETHING
	// if (this->_menuIndex == 1)
	// 	// Do SOMETHING
}