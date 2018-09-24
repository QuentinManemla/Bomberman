#include "ObjectManager.hpp"

ObjectManager::ObjectManager( Engine & engine ){
	this->engine = &engine;
	this->LM = new LevelManager(1); // may move this codeblock to a level init function to be available on call rather than this constructor
	this->map = this->LM->generateMap();
	this->player = new GameObject( PLAYER, new Vector3d(2, 2, 0.1f) );
	//this->placeEnemies( 1 ); // arbitrary int for now
}

ObjectManager::~ObjectManager( void ){
	delete this->LM;
}

void	ObjectManager::update( eControls key, double deltaTime){
	// PLAYER MOVE
	requestMove(this->player, key);

	// ENEMY MOVE
//	for (int i = 0; i < this->enemies.size(); i++){
//		if (this->enemies[i]->state == ALIVE)
//			this->engine->drawModel(PLAYER, (this->enemies[i]->position->vX), (this->enemies[i]->position->vY), 0.02f);
//			//AI(this->enemies[i]);
//	}
}

void	ObjectManager::render(void){
	std::cout << "PLAYER POS: " << this->player->position->vX << ";" << this->player->position->vY << std::endl; // debug
	// std::cout << "PLR TRUNC : " << trunc(this->player->position->vX) << ";" << trunc(this->player->position->vY) << std::endl; // debug
	this->engine->drawModel(PLAYER, (this->player->position->vX), (this->player->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	// std::cout << "OM render()" << std::endl; // debug
}


void	ObjectManager::requestMove(GameObject *actor, eControls key){
	// OTHER WAYS TO CAST
	//int truncX = round(actor->position->vX);
	//int truncY = round(actor->position->vY);
	//int truncX = static_cast<int>(actor->position->vX);
	//int truncY = static_cast<int>(actor->position->vY);

	// SET MODEL DIRECTION HERE

	// IF WILL CALL MOVE IF ACTOR IS NOT AT ITS DESTINATION YET
	int vectorDifference = 10;
	if ((vectorDifference = this->getVectorDifference(actor)) != 0){
		std::cout << "1vectorDifference = " << vectorDifference << std::endl; // debug
		move(actor, vectorDifference);
		return;
	}
	std::cout << "2vectorDifference = " << vectorDifference << std::endl; // debug

	int truncX = trunc(actor->position->vX);
	int truncY = trunc(actor->position->vY);

	actor->position->vX = static_cast<float>(truncX); // recentre object and mitigate precision issues
	actor->position->vY = static_cast<float>(truncY); // recentre object and mitigate precision issues

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

	// IF MOVE ALLOWED, SET NEW DESTINATION
	if (this->canMove(truncX, truncY) == 0){
		actor->destination->vX = truncX;
		actor->destination->vY = truncY;
		//std::cout << "x:"<< actor->destination->vX << " y:"<< actor->destination->vY << " z:"<< actor->destination->vZ << std::endl; // debug
	}
}

void	ObjectManager::move( GameObject *actor, int vectorDifference ){
	std::cout << "VD in move: " << vectorDifference << std::endl; // debug
	float move = 0;
	switch (vectorDifference){
		case 1:
			move = ((trunc(actor->position->vX * 10) / 10) > trunc(actor->destination->vX * 10) / 10 ? -0.1 : 0.1);
			//if (abs(actor->position->vX - actor->destination->vX) > 0.09)// test // debug // WORK BUT MOVE TO PRIMARY CONDITION
				actor->position->vX += move;
			//actor->position->vZ = getZStep(actor);
			break;
		case 2:
			move = (actor->position->vY > actor->destination->vY ? -0.1 : 0.1);
			actor->position->vY += move;
			break;
		case 3:
			move = (actor->position->vZ > actor->destination->vZ ? -0.1 : 0.1);
			actor->position->vZ += move;
			break;
	}
}

float	ObjectManager::getZStep( GameObject *actor){
	float ret = 0;

	actor->step++;
	if (actor->step >= 6)
		ret = ((10 - 6) / 10);
	else if (actor->step == 11)
		actor->step = 0;
	else
		ret = (actor->step / 10);
	return (ret);
}

int		ObjectManager::canMove(int x, int y){
	for (int i = 0; i < this->map.size(); i++){
		if (this->map[i]->position->vX == x && this->map[i]->position->vY == y)
			if (this->map[i]->state == ALIVE){
				// std::cout << "found " << this->map[i]->strType << " at " << this->map[i]->position->vX << ";" << this->map[i]->position->vY << std::endl; // debug
				return (1);
			}
			else {
				return (0);
			}
	}
	return (0);
}

void	ObjectManager::AI( GameObject *actor ){

	// requestMove( actor, key );
}

int		ObjectManager::getVectorDifference(GameObject *actor){
	if (trunc(actor->position->vX * 10) / 10 != trunc(actor->destination->vX * 10) / 10)
		return (1);
	else if (trunc(actor->position->vY * 10) / 10 != trunc(actor->destination->vY * 10) / 10)
		return (2);
	else if (trunc(actor->position->vZ * 10) / 10 != trunc(actor->destination->vZ * 10) / 10)
		return (3);
	return (0);
}

void	ObjectManager::placeEnemies( int level ){
	int x = 1;
	int y = 1;

	for ( y = 1; y <= this->LM->mapHeight; y++){
		for ( x = 1; x <= this->LM->mapWidth; x++){
			if ((this->canMove(x, y) == 0)){
				this->enemies.push_back(new GameObject( ENEMY, new Vector3d(x, y, 0.1f) ));
				std::cout << "placed at " << x << ";" << y << std::endl; // debug
				// exit(-1); // debug
				return; // test // debug// only returning here to limit enemies to 1 for now
			}
		}
	}
}