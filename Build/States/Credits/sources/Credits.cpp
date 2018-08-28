#include "../includes/Credits.hpp"

CreditsState::CreditsState( void ){
	std::cout << "Credits constructed" << std::endl;
}

CreditsState::~CreditsState( void ) {
	std::cout << "Credits destructed" << std::endl;
}

void CreditsState::update( void ){
	std::cout << "Credits update" << std::endl;
}

void CreditsState::render( void ){
	std::cout << "Credits render" << std::endl;
}