#include "GUIManager.hpp"

GUIManager::GUIManager( Engine & engine ) {
	this->engine = &engine;
}

GUIManager::GUIManager( void ) { return ; }

GUIManager::~GUIManager( void ) { return ; }

void		GUIManager::update( GameObject *player, int	elapsedSec, int playerScore, int level) {
	this->_lives = "Lives: " + std::to_string(player->hitPoints);
	if (elapsedSec > 0)
		this->_timeElapsed = "Time:  " + std::to_string(elapsedSec);
	else 
		this->_timeElapsed = "Time:  OVER!";
	this->_points = "Score: " + std::to_string(playerScore);
	this->_level = "Level: " + std::to_string(level);
}

void		GUIManager::render( void ) {
	this->engine->print2DText(this->_timeElapsed, 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
	this->engine->print2DText(this->_lives, 20, 50, 1.0f, 1.0f, 1.0f, 1.0f);
	this->engine->print2DText(this->_points, 20, 80, 1.0f, 1.0f, 1.0f, 1.0f);
	this->engine->print2DText(this->_level, 20, 110, 1.0f, 1.0f, 1.0f, 1.0f);
}