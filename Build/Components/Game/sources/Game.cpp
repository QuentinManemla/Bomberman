# include "../includes/Game.hpp"

Game::Game( void ){
	std::cout << "Game constructed" << std::endl; // debug
}

Game::~Game( void ){
	std::cout << "Game destructed" << std::endl; // debug
}

void Game::init( void ) {
	this->_engine.engineInit();
	this->_engine.state = INTRO; // set initial state
	this->_currentState = 0;
	_switchState();
}

void Game::run( void ) {
	_mainLoop();
}

void Game::_switchState( void ){
	switch (this->_engine.state){
		case INTRO:
			delete this->_currentState;
			this->_currentState = new IntroState(this->_engine);
			break;
		case MENU:
			delete this->_currentState;
			this->_currentState = new MenuState(this->_engine);
			break;
		case PLAY:
			delete this->_currentState;
			this->_currentState = new PlayState(this->_engine);
			break;
		case CREDITS:
			delete this->_currentState;
			this->_currentState = new CreditsState(this->_engine);
			break;
		case QUIT:
			delete this->_currentState;
			this->_currentState = new QuitState(this->_engine);
			break;
		case IDLE:
			break;
	};
	this->_engine.state = IDLE;
}

void Game::_mainLoop( void ){
	int 	quit;
	int		tick = 0;
	int		statetest = 0;
	double	startTime = 0;

	quit = 0;
	while (!(quit)){
		//std::cout << "elapsed time: " << glfwGetTime() - startTime << std::endl; // debug
		//std::cout << "ticks elapsed: " << tick++ << std::endl; // debug
		this->_currentState->update(this->_engine.getInput()); // update gets the key that is pressed
		this->_currentState->render();
		this->_switchState();

		std::cout << std::endl; // debug

		//usleep(16666); // simulate 60 fps

		//Frame rate manager
		this->_engine.FPSManager(/*startTime*/);
	}
}