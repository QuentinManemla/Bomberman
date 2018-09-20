#include "../includes/Play.hpp"

PlayState::PlayState( Engine & engine ) : _firstInit(true){
	this->_engine = &engine;
	this->_type = "Play";
	std::cout << "Play constructed" << std::endl;
	y = 0.0f;
	x = 0.0f;
	_positionTime = 0.0f;
	_positionPitch = 0.0f;
	this->_engine->triangle();
}

PlayState::PlayState( void ){
	std::cout << "Play constructed" << std::endl;
}

PlayState::~PlayState( void ){
	std::cout << "Play destructed" << std::endl;
}

void PlayState::update( eControls key ){
	static	int held = 1; // set to 1 initially to avoid accidental selection on state switch // debug // test
	std::cout << "Play update" << std::endl;
	if (key == ESCAPE){
		if (!(held))
			this->_engine->state = PAUSE;
		held = 1;
	}
	else if (key == IDLEKEY){
		held = 0;
	}
}

void PlayState::render( void ) {
	if ( this->_positionTime < 0.11f ) {
		this->_engine->_Camera.ProcessKeyboard(CAMERA_FORWARD, this->_positionTime);
		this->_positionTime += 0.01f;
	}
	// if ( this->_positionTime > 0.14f && this->_positionPitch < 80.0f) {
	// 	this->_engine->_Camera.ProcessMouseMovement(0, this->_positionPitch);
	// 	this->_positionPitch += 5.0f;
	// }
	std::cout << " Position: " << this->_positionTime << std::endl;
	this->_engine->clear();
	if (this->_engine->getInput() == UP) {
		y += 0.01f;
	} else if (this->_engine->getInput() == DOWN) {
		y -= 0.01f;
	} else if (this->_engine->getInput() == LEFT) {
		x -= 0.01f;
	} else if (this->_engine->getInput() == RIGHT) {
		x += 0.01f;
	} else if ( this->_engine->getInput() == ACTION ) {
		this->_engine->_Camera.ProcessMouseMovement(0, 0.05f);
	} else if ( this->_engine->getInput() == FIRE ) {
		this->_engine->_Camera.ProcessMouseMovement(0, -0.05f);
	}

	this->_engine->draw();
	this->_engine->drawModel(x, y, 0.1f);
	this->_engine->print2DText("Play", 20, 20, 0, 0, 0xff);
	this->_engine->render();
	std::cout << "Play render" << std::endl;
}

std::string PlayState::getType( void ){ //debug
	return this->_type;
}
