#include "../includes/Play.hpp"

PlayState::PlayState( void ){
	std::cout << "Play constructed" << std::endl;
}

PlayState::~PlayState( void ){
	std::cout << "Play destructed" << std::endl;
}

void PlayState::update( void ){
	std::cout << "Play update" << std::endl;
}

void PlayState::render( Engine & engine ){
	engine.render();
	std::cout << "Play render" << std::endl;
}