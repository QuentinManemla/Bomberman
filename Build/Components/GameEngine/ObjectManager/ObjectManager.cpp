#include "ObjectManager.hpp"

ObjectManager::ObjectManager( Engine & engine ){
	this->engine = &engine;
	LevelManager *LM = new LevelManager(1); // may move this codeblock to a level init function to be available on call rather than this constructor
	this->map = LM->generateMap();
	delete LM;
	this->player = new GameObject( PLAYER, new Vector3d(2, 2, 0.1f) );
}

ObjectManager::~ObjectManager( void ){

}

void	ObjectManager::update( eControls key, double deltaTime){
	requestMove(this->player, key);
	//for (int i = 0; i < this->enemies.size(); i++){
	//	canMove(this->enemies[i], key);
	//}

}

void	ObjectManager::render(void){
	std::cout << "PLAYER POS: " << this->player->position->vX << ";" << this->player->position->vY << std::endl;
	std::cout << "PLR TRUNC : " << trunc(this->player->position->vX) << ";" << trunc(this->player->position->vY) << std::endl;
	//this->engine->drawModel(PLAYER, (this->player->position->vX - 1) * 0.08f + (-0.48f), -((this->player->position->vY - 1) * 0.08f - 0.444f), 0.02f); // move math to drawModel()
//	this->engine->drawModel(PLAYER, (this->player->position->vX - 1) * 0.08f, -((this->player->position->vY - 0.5f) * 0.08f), 0.02f); // move math to drawModel()
	this->engine->drawModel(PLAYER, (this->player->position->vX), (this->player->position->vY), 0.02f); // move math to drawModel()
	std::cout << "OM render()" << std::endl;
}


void	ObjectManager::requestMove(GameObject *actor, eControls key){
	// OTHER WAYS TO CAST
	//int truncX = round(actor->position->vX);
	//int truncY = round(actor->position->vY);
	//int truncX = static_cast<int>(actor->position->vX);
	//int truncY = static_cast<int>(actor->position->vY);

	// SET MODEL DIRECTION HERE
	int vectorDifference = 10;
	if ((vectorDifference = this->getVectorDifference(actor)) != 0){
		std::cout << "1vectorDifference = " << vectorDifference << std::endl; // debug
		move(actor, vectorDifference);
		return;
	}
	std::cout << "2vectorDifference = " << vectorDifference << std::endl; // debug

	int truncX = trunc(actor->position->vX);// + 0.5f); // playing with offset
	int truncY = trunc(actor->position->vY);// + 0.5f); // playing with offset

	actor->position->vX = static_cast<flaot>(truncX);
	actor->position->vY = static_cast<flaot>(truncY);

	switch (key){
		case LEFT:
			truncX -= 1;
			std::cout << "LEFT" << std::endl;
			break;
		case UP:
			truncY -= 1;
			std::cout << "UP" << std::endl;
			break;
		case RIGHT:
			truncX += 1;
			std::cout << "RIGHT" << std::endl;
			break;
		case DOWN:
			truncY += 1;
			std::cout << "DOWN" << std::endl;
			break;
	}
	// if dir and block in that dir is occupied then no, just set dir
	//this->getObjectAtCoordinate(truncX, truncY);

	if (this->canMove(truncX, truncY) == 0){
		actor->destination->vX = truncX;
		actor->destination->vY = truncY;
		std::cout << "x:"<< actor->destination->vX << " y:"<< actor->destination->vY << " z:"<< actor->destination->vZ << std::endl; // debug
	}
	//	move(actor, key);
}

void	ObjectManager::move( GameObject *actor, int vectorDifference ){
	std::cout << "VD in move: " << vectorDifference << std::endl; // debug
	float move = 0;
	switch (vectorDifference){
		case 1:
			move = (actor->position->vX > actor->destination->vX ? -0.1 : 0.1);
			actor->position->vX += move; // 0.02f;
			break;
		case 2:
			move = (actor->position->vY > actor->destination->vY ? -0.1 : 0.1);
			actor->position->vY += move; // 0.02f;
			break;
		case 3:
			move = (actor->position->vZ > actor->destination->vZ ? -0.1 : 0.1);
			actor->position->vZ += move; // 0.02f;
			break;

	}
	// switch local dir depending on key parameter
	// if local dir = dir switch controls adding or subbing like nibbler
	// else GameObject dir = local dir
}

int		ObjectManager::canMove(int x, int y){
	for (int i = 0; i < this->map.size(); i++){
		if (this->map[i]->position->vX == x && this->map[i]->position->vY == y)
			if (this->map[i]->state == ALIVE){
				std::cout << "found " << this->map[i]->strType << " at " << this->map[i]->position->vX << ";" << this->map[i]->position->vY << std::endl;
				return (1);
			}
			else {
				return (0);
			}
	}
	return (0);
}

void	ObjectManager::checkCollision( void ){

}

int		ObjectManager::getVectorDifference(GameObject *actor){
	//std::trunc(100 * var) / 100
	if (trunc(actor->position->vX * 10) / 10 != trunc(actor->destination->vX * 10) / 10)
		return (1);
	else if (trunc(actor->position->vY * 10) / 10 != trunc(actor->destination->vY * 10) / 10)
		return (2);
	else if (trunc(actor->position->vZ * 10) / 10 != trunc(actor->destination->vZ * 10) / 10)
		return (3);
	return (0);
	/*
	if (actor->position->vX != actor->destination->vX)
		return (1);
	else if (actor->position->vY != actor->destination->vY)
		return (2);
	else if (actor->position->vZ != actor->destination->vZ)
		return (3);
	return (0);*/
}

/*
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
	*/