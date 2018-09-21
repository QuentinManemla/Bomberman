#include "ObjectManager.hpp"

ObjectManager::ObjectManager( Engine & engine ) : engine(engine){
	LevelManager *LM = new LevelManager(1); // may move this codeblock to a level init function to be available on call rather than this constructor
	this->map = LM->generateMap();
	delete LM;
	this->player = new GameObject( PLAYER, new Vector3d(2, 2, 0) );
}

ObjectManager::~ObjectManager( void ){

}

void	ObjectManager::update( eControls key, double deltaTime){
	move(key, this->player);
	// call canMove() to see if legal move based on key
	// if successfull call move()
	std::cout << "PLAYER POS: " << this->player->position->vX << ";" << this->player->position->vY << std::endl;
}

void	ObjectManager::render(void){
	//this->engine.drawModel(this->player->position->vX, this->player->position->vX, 0.1f);

}


void	ObjectManager::canMove(GameObject *GameObject, eControls key){
	// switch (key)
	// if dir and block in that dir is occupied then no, just set dir

}

void	ObjectManager::move( eControls key , GameObject *actor){
	switch (key){
		case UP:
			actor->position->vY += 0.01;
			break;
		case DOWN:
			actor->position->vY -= 0.01;
			break;
		case LEFT:
			actor->position->vX -= 0.01;
			break;
		case RIGHT:
			actor->position->vX += 0.01;
			break;
	}
	// switch local dir depending on key parameter
	// if local dir = dir switch controls adding or subbing like nibbler
	// else GameObject dir = local dir
}

void	ObjectManager::checkCollision( void ){

}
