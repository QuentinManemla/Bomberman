#include "../includes/Intro.hpp"


IntroState::IntroState( Engine & engine ){
	this->_engine = &engine;
	this->_type = "Intro";
	std::cout << "Intro constructed" << std::endl;
}

IntroState::IntroState( void ){
	std::cout << "Intro constructed" << std::endl;
}

IntroState::~IntroState( void ){
	std::cout << "Intro destructed" << std::endl;
}

void IntroState::update( eControls key ) {
	std::cout << "Intro update" << std::endl;
	static int time = 0; // test // debug
	time++; // test
	std::cout << "time: " << time << std::endl; // test
	this->_engine->triangle();
	this->_engine->clear();
	if (time == 1)
		this->_engine->playSound("Assets/Audio/Intro_State.wav", true);
	if (time >= 500){ // test // to be replaced by "end of intro/animation" flag
		this->_engine->stopSound();
		std::cout << "Intro over!" << std::endl;
		this->_engine->state = BACK;
	} else if (key == ENTER){
		this->_engine->stopSound();
		std::cout << "Skipping intro!" << std::endl;
		this->_engine->state = BACK;
	} else
		this->_engine->print2DText("Intro", 20, 20, 0, 0, 0xff);
}

void IntroState::render( void ) {
	this->_engine->draw();
	this->_engine->render();
	std::cout << "Intro render" << std::endl;
}

std::string IntroState::getType( void ){ //debug
	return this->_type;
}
