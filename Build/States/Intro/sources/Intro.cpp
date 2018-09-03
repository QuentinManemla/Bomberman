#include "../includes/Intro.hpp"

IntroState::IntroState( void ): _Textiteration(0) {
	std::cout << "Intro constructed" << std::endl;
}

IntroState::~IntroState( void ){
	std::cout << "Intro destructed" << std::endl;
}

void IntroState::update( Engine & engine ) {
	engine.clear();
	std::string		welcome = "Welcome to Bomberman";
	if (this->_Textiteration < welcome.length()) {
		engine.print2DText(welcome.substr(0 ,this->_Textiteration), 20, 20);
		this->_Textiteration++;
	} else if (this->_Textiteration == welcome.length()) {
		engine.print2DText(welcome, 20, 20);
		//engine.print2DText("Press any key to continue.", 20, 25);
	}
}

void IntroState::render( Engine	& engine ) {
	engine.render();
	std::cout << "Intro render" << std::endl;
}