#include "../includes/Play.hpp"

PlayState::PlayState( Engine & engine ){
	this->_engine = &engine;
	std::cout << "Play constructed" << std::endl;
}

PlayState::PlayState( void ){
	std::cout << "Play constructed" << std::endl;
}

PlayState::~PlayState( void ){
	std::cout << "Play destructed" << std::endl;
}

void PlayState::update( eControls key ){
	std::cout << "Play update" << std::endl;
	if (key == ESCAPE){
		this->_engine->state = MENU;
	}
}

void PlayState::render( void ){
	this->_engine->render();
	std::cout << "Play render" << std::endl;
}