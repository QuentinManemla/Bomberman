#include "../includes/Credits.hpp"

CreditsState::CreditsState( Engine & engine ){
	this->_engine = &engine;
	this->type = "Credits";
	std::cout << "Credits constructed" << std::endl;
}

CreditsState::CreditsState( void ){
	std::cout << "Credits constructed" << std::endl;
}

CreditsState::~CreditsState( void ) {
	std::cout << "Credits destructed" << std::endl;
}

void CreditsState::update( eControls key ){
	std::cout << "Credits update" << std::endl;
}

void CreditsState::render( void ){
	this->_engine->render();
	std::cout << "Credits render" << std::endl;
}

std::string CreditsState::getType( void ){ //debug
	return this->type;
}
