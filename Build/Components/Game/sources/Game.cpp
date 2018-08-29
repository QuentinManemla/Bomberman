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
	std::cout << "-Switch state?" << std::endl; // debug
	switch (this->_state){
		case INTRO:
			std::cout << "--Yup switch to Intro" << std::endl; // debug
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new IntroState;
			break;
		case MENU:
			std::cout << "--Yup switch to Menu" << std::endl; // debug
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new MenuState;
			break;
		case PLAY:
			std::cout << "--Yup switch to Play" << std::endl; // debug
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new PlayState;
			break;
		case CREDITS:
			std::cout << "--Yup switch to Credits" << std::endl; // debug
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new CreditsState;
			break;
		case QUIT:
			std::cout << "--Yup switch to Quit" << std::endl; // debug
			delete this->_currentState;
			this->_state = IDLE;
			this->_currentState = new QuitState;
			break;
		case IDLE:
			std::cout << "--Nope just chill" << std::endl; // debug
			break;
	};
}

void Game::_mainLoop( void ){
	int 	quit;
	int		tick = 0;
	int		statetest = 0;

	quit = 0;
	while (!(quit)){
		//std::cout << this->_engine.getKey() << std::endl;
		this->_currentState->render(this->_engine);
		this->_currentState->update(); // update gets the key that is pressed
		if (tick % 5 == 0)
			this->_state = static_cast<eState>(statetest++ % 5);
		this->_switchState();
		std::cout << std::endl; // debug
		tick++;
		usleep(1000000);
	}
}