#include "../includes/Options.hpp"

OptionsState::OptionsState( Engine & engine ){
	std::cout << "Options constructed" << std::endl; // debug
	this->_type = "Options";
	this->_engine = &engine;
	std::string arrOptionsMenu[4] = {"Controls", "Fullscreen", "Resolution", "Volume"};
	this->_optionsMenu.insert(this->_optionsMenu.end(), std::begin(arrOptionsMenu), std::end(arrOptionsMenu));
	this->_menuIndex = 0;
}

OptionsState::OptionsState( void ){
	std::cout << "Options constructed" << std::endl; // debug
}

OptionsState::~OptionsState( void ){
	std::cout << "Options destructed" << std::endl; // debug
}

void OptionsState::update( eControls key ){
	std::cout << "Options update" << std::endl; // debug
	this->_changeSelection( key );
}

void OptionsState::render( void ) {
	this->_engine->clear();
	this->_engine->printMenu(this->_optionsMenu, this->_menuIndex, "Assets/Images/main_menu_backgrond.png");
	this->_engine->render();
	std::cout << "Options render" << std::endl; // debug
}

void	OptionsState::_changeSelection( eControls key){
	if (this->_engine->menuHandler( key, this->_menuIndex, this->_optionsMenu.size() - 1 )){
		this->_makeSelection();
	}
}

void	OptionsState::_makeSelection( void){
	std::cout << "Selected " << this->_optionsMenu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	// update state depending on selection:
	/*if (this->_menuIndex == 0) // test
		this->_engine->state = PLAY; // test
	if (this->_menuIndex == 4) // test
		this->_engine->state = BACK; // test*/
}

std::string OptionsState::getType( void ){ //debug
	return this->_type;
}