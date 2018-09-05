#include "../includes/Menu.hpp"

MenuState::MenuState( Engine & engine ){
	std::cout << "Menu constructed" << std::endl; // debug
	this->_type = "Menu";
	this->_engine = &engine;
	std::string arrMainMenu[5] = {"New game", "Load game", "Options", "Credits", "Quit"};
	this->_mainMenu.insert(this->_mainMenu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
	this->_menuIndex = 0;
}

MenuState::MenuState( void ){
	std::cout << "Menu constructed" << std::endl; // debug
}

MenuState::~MenuState( void ){
	std::cout << "Menu destructed" << std::endl; // debug
}

void MenuState::update( eControls key ){
	std::cout << "Menu update" << std::endl; // debug
	this->_changeSelection( key );
}

void MenuState::render( void ) {
	this->_engine->clear();
	this->_engine->printMenu(this->_mainMenu, this->_menuIndex, "Assets/Images/main_menu_backgrond.png");
	this->_engine->render();
	std::cout << "Menu render" << std::endl; // debug
}

void	MenuState::_changeSelection( eControls key){
	static	int held = 1; // set to 1 initially to avoid accidental selection on state switch
	if (this->_engine->menuHandler( key, this->_menuIndex, this->_mainMenu.size() - 1, held )){
		this->_makeSelection();
	}
}

void	MenuState::_makeSelection( void ){
	std::cout << "Selected " << this->_mainMenu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	// reset _menuIndex; // (maybe? Only when not switching state I guess?)
	
	// update state depending on selection:
	if (this->_menuIndex == 0) // test
		this->_engine->state = PLAY; // test
	if (this->_menuIndex == 2){ // test
		this->_engine->state = OPTIONS; // test
	if (this->_menuIndex == 4) // test
		this->_engine->state = BACK; // test
}

std::string MenuState::getType( void ){ //debug
	return this->_type;
}
