#include "../includes/Menu.hpp"

MenuParentState::MenuParentState( Engine & engine ){
	this->_engine = &engine;
	this->_type = "MenuParent";
	std::cout << this->getType() << " constructed" << std::endl; // debug
	this->_menuIndex = 0;
}

MenuParentState::MenuParentState( void ){
	std::cout << this->getType() << " constructed" << std::endl; // debug
}

MenuParentState::MenuParentState(MenuParentState const & src) {}

MenuParentState	&MenuParentState::operator=(MenuParentState const &rhs) {}

MenuParentState::~MenuParentState( void ){
	std::cout << this->getType() << " destructed" << std::endl; // debug
}

void MenuParentState::update( eControls key ){
	std::cout << this->getType() << " update" << std::endl; // debug
	this->_changeSelection( key );
}

void MenuParentState::render( void ) {
	this->_engine->clear();
	this->_engine->printMenu(this->_menu, this->_type, this->_menuIndex, "Assets/Images/main_menu_backgrond.png");
	this->_engine->render();
	std::cout << this->getType() << " render" << std::endl; // debug
}

void	MenuParentState::_changeSelection( eControls key){
	if (this->_engine->menuHandler( key, this->_menuIndex, this->_menu.size() - 1 )){
		this->_makeSelection();
	}
}

std::string MenuParentState::getType( void ) { //debug
	return this->_type;
}
