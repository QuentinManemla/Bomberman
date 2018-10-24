# include "../includes/Game.hpp"

Game::Game( void ){
	std::cout << "Game constructed" << std::endl; // debug
	
	this->_engine.engineInit();

	this->_stateStack.push(new QuitState(this->_engine));
	this->_stateStack.push(new MenuState(this->_engine));

	this->_engine.state = INTRO; // set initial state
	_switchState();
}

Game::Game(Game const & src) {
	this->_engine = src._engine;
}

Game	&Game::operator=(Game const &rhs) {
	return *(new Game(rhs));
}

Game::~Game( void ){
	std::cout << "Game destructed" << std::endl; // debug
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
				this->_engine._SoundEngine.playSoundSource(this->_engine._SoundEngine._Menu, true);
				this->_stateStack.push(new MenuState(this->_engine));
				break;
			case PLAY:
				this->_stateStack.push(new PlayState(this->_engine));
				break;
			case PLAYLOADGAME:
				this->_stateStack.push(new PlayState(this->_engine, "./.save/save.save", false));
				break;
			case RESTARTLEVEL:
				delete this->_stateStack.top();
				this->_stateStack.pop();
				this->_stateStack.push(new PlayState(this->_engine, "./.save/save.save", true));
				break;
			case FAIL:
				this->_stateStack.push(new FailState(this->_engine));
				break;
			case CREDITS:
				this->_engine.setResolution(1920, 1080);
				this->_engine.setFullScreen();
				this->_stateStack.push(new CreditsState(this->_engine));
				break;
			case SUCCESS:
				this->_stateStack.push(new WinState(this->_engine));
				break;
			case CONTINUE:
				this->_stateStack.push(new PlayState(this->_engine, true));
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
			case CONTROLS:
				this->_stateStack.push(new OptionsControlsState(this->_engine));
				break;
			case RESOLUTION:
				this->_stateStack.push(new OptionsResolutionState(this->_engine));
				break;
			case FULLSCREEN:
				this->_stateStack.push(new OptionsFullScreenState(this->_engine));
				break;
			case SAVEQUIT:
				this->_stateStack.push(new SaveQuitState(this->_engine));
				break;
			case LOADGAME:
				this->_stateStack.push(new LoadGameState(this->_engine));
				break;
			case VOLUME:
				this->_stateStack.push(new OptionsVolumeState(this->_engine));
				break;
			case BACK:
				if (this->_stateStack.top()->getType() != "Quit"){ // special case when esc is pressed in quit state
					delete this->_stateStack.top();
					this->_stateStack.pop();
				}
				break;
			case BACK_TO_MAIN:
				while (this->_stateStack.top()->getType() != "Menu"){ // traverse all the way back to main menu
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
			default:
				break;
		};
		this->_engine.state = IDLE;
	}
}

void Game::_mainLoop( void ){
	int 	quit;

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