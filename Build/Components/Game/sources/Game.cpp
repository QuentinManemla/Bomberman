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
	//std::cout << "-Switch state?" << std::endl; // debug
	switch (this->_engine.state){
		case INTRO:
			//std::cout << "--Yup switch to Intro" << std::endl; // debug
			delete this->_currentState;
			this->_currentState = new IntroState(this->_engine);
			break;
		case MENU:
			//std::cout << "--Yup switch to Menu" << std::endl; // debug
			delete this->_currentState;
			this->_currentState = new MenuState(this->_engine);
			break;
		case PLAY:
			//std::cout << "--Yup switch to Play" << std::endl; // debug
			delete this->_currentState;
			this->_currentState = new PlayState(this->_engine);
			break;
		case CREDITS:
			//std::cout << "--Yup switch to Credits" << std::endl; // debug
			delete this->_currentState;
			this->_currentState = new CreditsState(this->_engine);
			break;
		case QUIT:
			//std::cout << "--Yup switch to Quit" << std::endl; // debug
			delete this->_currentState;
			this->_currentState = new QuitState(this->_engine);
			break;
		case IDLE:
			//std::cout << "--Nope just chill" << std::endl; // debug
			break;
	};
	this->_engine.state = IDLE;
}

void Game::_mainLoop( void ){
	int 	quit;
	int		tick = 0;
	int		statetest = 0;

	quit = 0;
	while (!(quit)){
		std::cout << "gameloop debug: " << std::endl << this->_engine.getInput() << std::endl; // test debug
		this->_currentState->update(this->_engine.getInput()); // update gets the key that is pressed
		this->_currentState->render();
		this->_switchState();
		//this->_engine.frameManager();

		/* switch testing
		if (tick % 5 == 0)
			this->_state = static_cast<eState>(statetest++ % 5);
		tick++;
		*/
		std::cout << std::endl; // debug
		usleep(16666); // simulate 60 fps
	}
}