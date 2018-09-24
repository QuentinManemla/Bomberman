#include "../includes/Play.hpp"

PlayState::PlayState( Engine & engine ){ // first init?
	this->_engine = &engine;
	this->_type = "Play";
	std::cout << "Play constructed" << std::endl;
	this->_isPlaying = false;
	start_y = 0.48f;
	y = 0.48f;
	x = -0.48f;
	start_x = -0.48f;
	_positionTime = 0.0f;
	_positionPitch = 0.0f;
	this->_engine->triangle();
	this->_OM = new ObjectManager();
}

PlayState::PlayState( void ){
	std::cout << "Play constructed" << std::endl;
}

PlayState::~PlayState( void ){
	this->_engine->_Camera.init(glm::vec3(0.0f, 0.0f, 3.0f));
	this->_engine->stopSound();
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

void PlayState::drawMap( void ) {
	for (int i = 0; i < this->_OM->map.size(); i++) {
		float ModelX = (this->_OM->map[i]->position->vX - 1) * 0.08f + start_x;
		float ModelY = (this->_OM->map[i]->position->vY - 1) * 0.08f - start_y;
		this->_engine->drawModel(this->_OM->map[i]->eType, ModelX, -ModelY, 0.02f);
	}
}

void PlayState::render( void ) {
	if (!_isPlaying) {
		this->_engine->playSound("Assets/Audio/Bomberman-Music.wav", true);
		this->_isPlaying = true;
	}
	if ( this->_positionTime < 0.11f ) {
		this->_engine->_Camera.ProcessKeyboard(CAMERA_FORWARD, this->_positionTime);
		this->_positionTime += 0.01f;
	}
	std::cout << " Position: " << this->_positionTime << std::endl;
	this->_engine->clear();
	if (this->_engine->getInput() == UP) {
		y += 0.01f;
		//this->_engine->_Camera.ProcessKeyboard(CAMERA_FORWARD, 0.09f);
	} else if (this->_engine->getInput() == DOWN) {
		y -= 0.01f;
		//this->_engine->_Camera.ProcessKeyboard(CAMERA_BACKWARD, 0.09f);
	} else if (this->_engine->getInput() == LEFT) {
		x -= 0.01f;
	} else if (this->_engine->getInput() == RIGHT) {
		x += 0.01f;
	} else if ( this->_engine->getInput() == ACTION ) {
		this->_engine->_Camera.ProcessMouseMovement(0, 1.0f);
	} else if ( this->_engine->getInput() == FIRE ) {
		this->_engine->_Camera.ProcessMouseMovement(0, -1.0f);
	}
	this->drawMap();
	this->_engine->draw();
	std::cout << "X: " << x << " Y: " << y << std::endl;
	this->_engine->drawModel(PLAYER,x - 0.1f, y, 0.02f);
	//this->_engine->print2DText("Play", 20, 20, 0, 0, 0xff);
	this->_engine->render();
	std::cout << "Play render" << std::endl;
}

std::string PlayState::getType( void ){ //debug
	return this->_type;
}
