#include "../includes/Play.hpp"

PlayState::PlayState( Engine & engine ) { // first init?
	this->_engine = &engine;
	this->_type = "Play";
	std::cout << "Play constructed" << std::endl;

	_positionTime = 0.0f;
	_positionPitch = 0.0f;
	this->_isPlaying = false;
	//this->begin = std::chrono::steady_clock::now(); MAY NEED
	this->_engine->backgroundTexture("Assets/Textures/stone-wall.jpg");

	this->_OM = new ObjectManager( engine );
	this->_GM = new GUIManager( engine );
}

PlayState::PlayState( void ){
	std::cout << "Play constructed" << std::endl;
}

PlayState::~PlayState( void ){
	this->_engine->_Camera.init(glm::vec3(0.48f, -1.1f, 2.7f));
	this->_engine->stopSound();
}

void PlayState::update( eControls key ){
	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//
	//this->_elapsedSec = std::chrono::duration_cast<std::chrono::seconds>(end - this->startTime).count();
	//this->_remainingTime = (this->_OM->LM->duration - this->_elapsedSec) > 0 ? this->_OM->LM->duration - this->_elapsedSec : 0;


	this->_engine->_Save.health = this->_OM->player->hitPoints;
	this->_engine->_Save.level = this->_OM->LM->level;
	this->_engine->_Save.points = this->_OM->playerScore;
	this->_engine->_Save.remainingTime = this->_remainingTime;

	// std::cout << "TIME ELAPSED: " << this->_elapsedSec << std::endl;
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
	this->_OM->update(key/*, this->_remainingTime*/);
	this->_GM->update(this->_OM->player, this->_OM->displayTime, this->_OM->playerScore);
}

void PlayState::drawMap( void ) { // needs to move to render engine
	float ModelX = 0;
	float ModelY = 0;

	for (int i = 0; i < this->_OM->map.size(); i++) {
		if (this->_OM->map[i]->state == ALIVE){
			ModelX = (this->_OM->map[i]->position->vX);
			ModelY = (this->_OM->map[i]->position->vY);
			this->_engine->drawModel(this->_OM->map[i]->eType, ModelX, ModelY, 0.02f);
		}
	}
}

void PlayState::render( void ) {
	if (!_isPlaying) {
		this->_engine->_SoundEngine.playSoundSource(this->_engine->_SoundEngine._Play, true);
		this->_isPlaying = true;
	}
	if ( this->_positionPitch < 7.5f) {
		this->_engine->_Camera.ProcessMouseMovement(0.0f, this->_positionPitch);
		this->_positionPitch += 0.1f;
	}
	if ( this->_positionTime < 0.11f ) {
		this->_engine->_Camera.ProcessKeyboard(CAMERA_FORWARD, this->_positionTime);
		this->_positionTime += 0.01f;
	}
	this->_engine->clear();
	this->drawMap(); // move to engine
	this->_engine->drawBackground(); //rename
	this->_OM->render();
	this->_GM->render();
	this->_engine->render();
	std::cout << "Play render" << std::endl;
}

std::string PlayState::getType( void ){ //debug
	return this->_type;
}
