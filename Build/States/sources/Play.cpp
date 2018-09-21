#include "../includes/Play.hpp"

PlayState::PlayState( Engine & engine ) : _firstInit(true){ // first init?
	this->_engine = &engine;
	this->_type = "Play";
	std::cout << "Play constructed" << std::endl;

	start_y = 0.44f;
	y = 0.44f;
	x = -0.44f;
	start_x = -0.44f;
	_positionTime = 0.0f;
	_positionPitch = 0.0f;
	this->_engine->triangle();
	this->_OM = new ObjectManager();
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
	if ( this->_positionTime < 0.09f ) {
		this->_engine->_Camera.ProcessKeyboard(CAMERA_FORWARD, this->_positionTime);
		this->_positionTime += 0.01f;
	}
	// std::cout << "==========" << std::endl;
	// std::cout << "Vector X: " << this->_OM->map[2]->position->vX << std::endl;
	// std::cout << "Vector Y: " << this->_OM->map[2]->position->vY << std::endl;
	// std::cout << "Vector Z: " << this->_OM->map[1]->position->vZ << std::endl;
	// std::cout << "==========" << std::endl;
	// std::cout << "==========" << std::endl;
	// std::cout << "ACTUAL Vector X: " << (this->_OM->map[2]->position->vX - 1) * start_x + 0.09f << std::endl;
	// std::cout << "ACTUAL Vector Y: " << this->_OM->map[2]->position->vY << std::endl;
	// std::cout << "ACTUAL Vector Z: " << this->_OM->map[0]->position->vZ << std::endl;
	// std::cout << "==========" << std::endl;
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

	for (int i = 0; i < this->_OM->map.size(); i++) {
		if (this->_OM->map[i]->strType == "SolidWall")
			this->_engine->drawModel((this->_OM->map[i]->position->vX - 1) * 0.08f + start_x, (this->_OM->map[i]->position->vY - 1) * 0.08f - start_y, 0.1f);
		if (this->_OM->map[i]->strType == "Wall")
			this->_engine->drawModel2((this->_OM->map[i]->position->vX - 1) * 0.08f + start_x, (this->_OM->map[i]->position->vY - 1) * 0.08f - start_y, 0.1f);
		std::cout << "==========" << std::endl;
		std::cout << "Vector X: " << this->_OM->map[i]->position->vX << std::endl;
		std::cout << "Vector Y: " << this->_OM->map[i]->position->vY << std::endl;
		std::cout << "Vector Y: " << this->_OM->map[i]->position->vZ << std::endl;
		std::cout << "==========" << std::endl;
	}
	this->_engine->draw();
	std::cout << "X: " << x << "Y: " << y << std::endl;
	//this->_engine->drawModel(x, y, 0.1f);
	this->_engine->print2DText("Play", 20, 20, 0, 0, 0xff);
	this->_engine->render();
	std::cout << "Play render" << std::endl;
}

std::string PlayState::getType( void ){ //debug
	return this->_type;
}
