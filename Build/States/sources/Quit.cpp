#include "../includes/Quit.hpp"

QuitState::QuitState( Engine & engine ){
	std::cout << "Quit constructed" << std::endl;
	this->type = "Quit";
	this->_engine = &engine;
}

QuitState::QuitState( void ){
	std::cout << "Quit constructed" << std::endl;
}

QuitState::~QuitState( void ){
	std::cout << "Quit destructed" << std::endl;
}

void QuitState::update( eControls key ){
	std::cout << "Quit update" << std::endl;
	exit(0); // test
}

void QuitState::render( void ){
	this->_engine->render();
	std::cout << "Quit render" << std::endl;
}

std::string QuitState::getType( void ){ //debug
	return this->type;
}
