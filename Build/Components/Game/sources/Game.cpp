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
	this->_currentState = 0;
	_switchState();
}

void Game::run( void ) {
	_mainLoop();
}

void Game::_switchState( void ){
	switch (this->_state){
		case INTRO:
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new IntroState;
			break;
		case MENU:
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new MenuState;
			break;
		case PLAY:
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new PlayState;
			break;
		case CREDITS:
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new CreditsState;
			break;
		case QUIT:
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new QuitState;
			break;
		case IDLE:
			break;
	};
}

void Game::_mainLoop( void ){
	int 	quit;
	int		tick = 0;

	quit = 0;
	while (!(quit)){
		// get input
		this->_currentState->render(this->_engine);
		this->_currentState->update();
		if (tick == 5)
			this->_state = MENU;
		this->_switchState();
		tick++;
		usleep(1000000);
	}
}