# include "../includes/Game.hpp"

Game::Game( void ){
	std::cout << "Game constructed" << std::endl; // debug
	this->_stateStack.push(new QuitState(this->_engine));
	this->_stateStack.push(new MenuState(this->_engine));
}

Game::~Game( void ){
	std::cout << "Game destructed" << std::endl; // debug
}

void Game::init( void ) {
	this->_engine.engineInit();
	this->_engine.state = INTRO; // set initial state
	_switchState();
}

void Game::run( void ) {
	_mainLoop();
}

void Game::_switchState( void ){
	if (this->_engine.state != IDLE){
		this->_engine.held = 1; // test
		switch (this->_engine.state){
			case IDLE:
				break;
			case INTRO:
				this->_stateStack.push(new IntroState(this->_engine));
				break;
			case MENU:
				this->_stateStack.push(new MenuState(this->_engine));
				break;
			case PLAY:
				this->_stateStack.push(new PlayState(this->_engine));
				break;
			case CREDITS:
				this->_stateStack.push(new CreditsState(this->_engine));
				break;
			case QUIT:
				this->_stateStack.push(new QuitState(this->_engine));
				break;
			case PAUSE:
				this->_stateStack.push(new PauseState(this->_engine));
				break;
			case OPTIONS:
				this->_stateStack.push(new OptionsState(this->_engine));
				break;
			case BACK:
				if (this->_stateStack.top()->getType() != "Quit"){ // special case when esc is pressed in quit state
					delete this->_stateStack.top();
					this->_stateStack.pop();
				}
				break;
			case BACK_TO_MAIN:
				while (this->_stateStack.top()->getType() != "Menu"){
					std::cout << "TPYE: " << this->_stateStack.top()->getType() << std::endl;
					delete this->_stateStack.top();
					this->_stateStack.pop();
				}
				break;
			case EXIT:
				delete this->_stateStack.top();
				this->_stateStack.pop();
				exit(0);
				break;
		};
		this->_engine.state = IDLE;
	}
}

void Game::_mainLoop( void ){
	int 	quit;
	int		tick = 0;
	int		statetest = 0;
	double	startTime = 0;

	quit = 0;
	while (!(quit)){
		std::cout << "debug key: " << this->_engine.getInput() << std::endl; // debug
		this->_stateStack.top()->update(this->_engine.getInput());
		this->_stateStack.top()->render();
		this->_switchState();

		this->debugprintstack();// debug
		std::cout << std::endl; // debug

		//Frame rate manager
		this->_engine.FPSManager(/*startTime*/);
	}
}

void	Game::debugprintstack(){ // debug
	for (std::stack<IState*> dump = this->_stateStack; !dump.empty(); dump.pop())
		std::cout << dump.top()->getType() << '-';
	std::cout << std::endl;
}