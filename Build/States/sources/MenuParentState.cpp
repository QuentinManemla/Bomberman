#include "../includes/Menu.hpp"

MenuParentState::MenuParentState( Engine & engine ){
	this->_type = "MenuParent";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_menuIndex = 0;
}

MenuParentState::MenuParentState( void ){
	std::cout << this->getType() << " constructed" << std::endl; // debug
}

MenuParentState::~MenuParentState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void MenuParentState::update( eControls key ){
	std::cout << this->getType() << " update" << std::endl; // debug
	this->_changeSelection( key );
}

void MenuParentState::render( void ) {
	this->_engine->clear();
	this->_engine->printMenu(this->_menu, this->_menuIndex, "Assets/Images/main_menu_backgrond.png");
	this->_engine->render();
	std::cout << this->getType() << " render" << std::endl; // debug
}

void	MenuParentState::_changeSelection( eControls key){
	if (this->_engine->menuHandler( key, this->_menuIndex, this->_menu.size() - 1 )){
		this->_makeSelection();
	}
}
/*
void	MenuParentState::_makeSelection( void ){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	// update state depending on selection:
	if (this->_menuIndex == 0) // test
		this->_engine->state = PLAY; // test
	if (this->_menuIndex == 2) // test
		this->_engine->state = OPTIONS; // test
	if (this->_menuIndex == 4) // test
		this->_engine->state = BACK; // test
	std::cout << "no if" << std::endl;

}
*/
std::string MenuParentState::getType( void ) { //debug
	return this->_type;
}
