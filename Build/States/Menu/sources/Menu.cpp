#include "../includes/Menu.hpp"

MenuState::MenuState( void ){
	std::cout << "Menu constructed" << std::endl;
}

MenuState::~MenuState( void ){
	std::cout << "Menu destructed" << std::endl;
}

void MenuState::update( void ){
	std::cout << "Menu update" << std::endl;
}

void MenuState::render( Engine	&engine ){
	engine.render();
}