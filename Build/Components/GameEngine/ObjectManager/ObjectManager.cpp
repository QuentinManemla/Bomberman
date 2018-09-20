#include "ObjectManager.hpp"

ObjectManager::ObjectManager( void ){
	LevelManager *LM = new LevelManager(1); // may move this codeblock to a level init function to be available on call rather than this constructor
	this->map = LM->generateMap();
	delete LM;
	this->player = new GameObject( PLAYER, new Vector3d(1, 1, 0) );
}

ObjectManager::~ObjectManager( void ){

}

void	ObjectManager::update( eControls key, double deltaTime){

}

void	ObjectManager::canMove(GameObject *GameObject, eControls key){

}

void	ObjectManager::checkCollision( void ){

}
