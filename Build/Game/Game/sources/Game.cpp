#include "../includes/Game.hpp"

Game::Game( void ){
	std::cout << "Game constructed" << std::endl; // debug
}

Game::~Game( void ){
	std::cout << "Game destructed" << std::endl; // debug
}

void Game::init( void ){
	
}

void Game::_switchState( void ){
	delete this->_currentState;
	switch (sys->state){ // need to pass Game engine pointer to state
		case INTRO:
			this->_currentState = new InstroState intro;
			break;
		case MENU:
			this->_currentState = new MenuState;
			break;
		case PLAY:
			this->_currentState = new PlayState;
			break;
		case CREDITS:
			this->_currentState = new CreditsState;
			break;
		case QUIT:
			this->_currentState = new QuitState;
			break;
	};
}

void Game::_mainLoop( void ){
	// current state can get a reference to quit as well as system struct (like env)
	while (!(quit)){
		// get input
		this->_currentState->update();
		this->_currentState->render();
		usleep(1000000);
	}
}