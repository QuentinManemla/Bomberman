#include "../includes/Game.hpp"

Game::Game( void ){return ;}

Game::~Game( void ){return ;}

void Game::init( void ){
	
}

void Game::_switchState( void ){

}

void Game::_mainLoop( void ){
	// current state can get a reference to quit as well as system struct (like env)
	while (!(quit)){
		// get input
		this->_currentState->update();
		this->_currentState->render();
	}
}