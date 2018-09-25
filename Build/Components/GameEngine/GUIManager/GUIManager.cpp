#include "GUIManager.hpp"

GUIManager::GUIManager( Engine & engine ) {
	this->engine = &engine;
}

GUIManager::GUIManager( void ) { return ; }

GUIManager::~GUIManager( void ) { return ; }

void		GUIManager::update( GameObject *player, int	elapsedSec) {
	this->_lives = "Lives: 1";
	this->_timeElapsed = "Time: " + std::to_string(elapsedSec);
}

void		GUIManager::render( void ) {
	this->engine->print2DText(this->_timeElapsed, 20, 20, 1.0f, 0.0f, 0.0f, 1.0f);
	this->engine->print2DText(this->_lives, 20, 50, 1.0f, 0.0f, 0.0f, 1.0f);
}