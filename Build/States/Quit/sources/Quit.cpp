#include "../includes/Quit.hpp"

QuitState::QuitState( void ){
	std::cout << "Quit constructed" << std::endl;
}

QuitState::~QuitState( void ){
	std::cout << "Quit destructed" << std::endl;
}

void QuitState::update( void ){
	std::cout << "Quit update" << std::endl;
}

void QuitState::render( Engine & engine ){
	engine.render();
	std::cout << "Quit render" << std::endl;
}