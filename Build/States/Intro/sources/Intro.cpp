#include "../includes/Intro.hpp"

IntroState::IntroState( void ){
	std::cout << "Intro constructed" << std::endl;
}

IntroState::~IntroState( void ){
	std::cout << "Intro destructed" << std::endl;
}

void IntroState::update( void ) {
	std::cout << "Intro update" << std::endl;
}

void IntroState::render( Engine	&engine ) {
	engine.render();
	std::cout << "Intro render" << std::endl;
}