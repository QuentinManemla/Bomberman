#include "../includes/Pause.hpp"

PauseState::PauseState( Engine & engine ){
	std::cout << "Pause constructed" << std::endl; // debug
	this->_type = "Pause";
	this->_engine = &engine;
	std::string arrPauseMenu[3] = {"Resume", "Save and quit to menu", "Quit to menu"};
	this->_pauseMenu.insert(this->_pauseMenu.end(), std::begin(arrPauseMenu), std::end(arrPauseMenu));
	this->_menuIndex = 0;
}

PauseState::PauseState( void ){
	std::cout << "Pause constructed" << std::endl; // debug
}

PauseState::~PauseState( void ){
	std::cout << "Pause destructed" << std::endl; // debug
}

void PauseState::update( eControls key ){
	std::cout << "Pause update" << std::endl; // debug
	this->_changeSelection( key );
}

void PauseState::render( void ) {
	this->_engine->clear();
	this->_engine->printMenu(this->_pauseMenu, this->_menuIndex, "Assets/Images/main_menu_backgrond.png");
	this->_engine->render();
	std::cout << "Pause render" << std::endl; // debug
}

void	PauseState::_changeSelection( eControls key){
	//static	int held = 1; // set to 1 initially to avoid accidental selection on state switch
	if (this->_engine->menuHandler( key, this->_menuIndex, this->_pauseMenu.size() - 1 )){
		this->_makeSelection();
	}
}

void	PauseState::_makeSelection( void ){
	std::cout << "Selected " << this->_pauseMenu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	// reset _menuIndex; // (maybe? Only when not switching state I guess?)
	
	// update state depending on selection:
	if (this->_menuIndex == 0) // test
		this->_engine->state = BACK; // test
/*	else if (this->_menuIndex == 2)
		this->_engine->state = BACK_TO_MAIN;*/
}

std::string PauseState::getType( void ){ //debug
	return this->_type;
}