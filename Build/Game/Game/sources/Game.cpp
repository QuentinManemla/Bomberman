# include "../includes/Game.hpp"

Game::Game( void ){
	std::cout << "Game constructed" << std::endl; // debug
}

Game::~Game( void ){
	std::cout << "Game destructed" << std::endl; // debug
}

void Game::init( void ) {
	this->_engine.engineInit();
	this->_state = INTRO;
	_switchState();
}

void Game::run( void ) {
	_mainLoop();
}

void Game::_switchState( void ){
	switch (this->_state){
		case INTRO:
			this->_currentState = new IntroState;
		default:
			break;
	};
}

void Game::_mainLoop( void ){
	int 	quit;

	quit = 0;
	while (!(quit)){
		// get input
		this->_currentState->render(this->_engine);
		this->_currentState->update();
		usleep(1000000);
	}
}