#include "ObjectManager.hpp"

ObjectManager::ObjectManager( Engine & engine ){
	this->engine = &engine;
	this->LM = new LevelManager(1); // may move this codeblock to a level init function to be available on call rather than this constructor
	this->map = this->LM->generateMap();
	this->player = new Player( PLAYER, new Vector3d(2, 2, 0.1f) );
	this->enemies.push_back(new Enemy( ENEMY, new Vector3d(3, 2, 0.1f) )); // test // debug
	this->enemies.push_back(new Enemy( ENEMY, new Vector3d(3, 2, 0.1f) )); // test // debug
	this->bomb = NULL;
	//this->placeEnemies( 1 ); // arbitrary int for now

	//SOME VALUES CHANGE BASED ON POWER UP: THESE ARE STARTING VALUES
	this->fuseTime = 3.0f;
	this->bombRadius = 1;
}

ObjectManager::~ObjectManager( void ){
	delete this->LM;
}

void	ObjectManager::update( eControls key, double deltaTime){
	// PLAYER MOVE
	requestMove(this->player, key);

	// ENEMY MOVE
	for (int i = 0; i < this->enemies.size(); i++){
		if (this->enemies[i]->state == ALIVE)
			requestEnemyMove(this->enemies[i]);
	}

	// INCREMENT BOMB FUSE
	if (this->bomb != NULL){
		if (this->bomb->state == ALIVE){
			this->bomb->fuseTime -= 0.016f; // to be replaced with deltaTime
			if (this->bomb->fuseTime < 0)
				this->explode();
		}
	}
}

void	ObjectManager::render(void){
	std::cout << "PLAYER POS: " << this->player->position->vX << ";" << this->player->position->vY << std::endl; // debug
	// std::cout << "PLR TRUNC : " << trunc(this->player->position->vX) << ";" << trunc(this->player->position->vY) << std::endl; // debug
	this->engine->drawModel(PLAYER, (this->player->position->vX), (this->player->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	for (int i = 0; i < this->enemies.size(); i++){
		if (this->enemies[i]->state == ALIVE)
			this->engine->drawModel(PLAYER, (this->enemies[i]->position->vX), (this->enemies[i]->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	}
	if (this->bomb != NULL)
		this->engine->drawModel(PLAYER, (this->bomb->position->vX), (this->bomb->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
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

	this->getForward(key, &truncX, &truncY);

	// IF MOVE ALLOWED, SET NEW DESTINATION
	if (this->isOpen(truncX, truncY)){
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

int		ObjectManager::isOpen(int x, int y){
	if (this->bomb != NULL)
		if (x == this->bomb->position->vX && y == this->bomb->position->vY) // debug
			return (0);
	for (int i = 0; i < this->map.size(); i++){
		if (this->map[i]->position->vX == x && this->map[i]->position->vY == y)
			if (this->map[i]->state == ALIVE)
				return (0);
			else
				return (1);
	}
	return (1);
}

int		ObjectManager::isMortal(int x, int y){
	for (int i = 0; i < this->map.size(); i++){
		if (this->map[i]->position->vX == x && this->map[i]->position->vY == y)
			if (this->map[i]->mortal == 1)
				return (1);
			else
				return (0);
	}
	return (0);
}

void	ObjectManager::requestEnemyMove( GameObject *actor ){
	int x = actor->position->vX;
	int y = actor->position->vY;

	int forwardX = x;
	int forwardY = y;

	getForward(actor->currentDirection, &forwardX, &forwardY);
	if (isOpen(forwardX, forwardY) == 0)
		getOpenDirection(actor);
	else if (actor->stuck != 1){
		this->requestMove(actor, actor->currentDirection);
	}
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
			if ((this->isOpen(x, y) == 0)){
				this->enemies.push_back(new GameObject( ENEMY, new Vector3d(x, y, 0.1f) ));
				std::cout << "placed at " << x << ";" << y << std::endl; // debug
				return; // test // debug// only returning here to limit enemies to 1 for now
			}
		}
	}
}

bool	ObjectManager::isAtDestination( GameObject *actor){
	if ((actor->position->vX == actor->destination->vX) && (actor->position->vY == actor->destination->vY))
		return (1);
	return (0);
}

void	ObjectManager::getForward( eControls key, int *x, int *y){
	switch (key){
		case LEFT:
			*x -= 1;
			break;
		case UP:
			*y -= 1;
			break;
		case RIGHT:
			*x += 1;
			break;
		case DOWN:
			*y += 1;
			break;
	}
}

// SETS ENEMY CURRENT DIR TO OPEN DIRECTION, STETS STUCK FLAG
void	ObjectManager::getOpenDirection( GameObject *actor ){
	int	start = (rand() % 4);
	int	tries = 4;

	int	x = actor->position->vX;
	int	y = actor->position->vY;

	actor->stuck = 0;
	while (tries-- != 0){
		switch (start){
			case 0:
				if (isOpen(x - 1, y)){
					std::cout << "return left" << std::endl;
					actor->currentDirection = LEFT;
					return;
				}
			case 1:
				if (isOpen(x, y - 1)){
					std::cout << "return up" << std::endl;
					actor->currentDirection = UP;
					return;
				}
			case 2:
				if (isOpen(x + 1, y)){
					std::cout << "return right" << std::endl;
					actor->currentDirection = RIGHT;
					return;
				}
			case 3:
				if (isOpen(x, y + 1)){
					std::cout << "return down" << std::endl;
					actor->currentDirection = DOWN;
					return;
				}
		}
		start = start++ % 4;
	}
	actor->stuck = 1;
}

void	ObjectManager::placeBomb( void ){
	// check for bomb related powerup and then change bomb params accordingly
	if (this->bomb == NULL)
		this->bomb = new Bomb(BOMB, new Vector3d(this->player->destination->vX, this->player->destination->vY, this->player->destination->vZ), this->fuseTime); // params subject to powerup
}

void	ObjectManager::explode( void ){
	// check if bomb related powerup - adjust values as necessary
	// push values to bomb positional array
	// check open dirs for bomb
	// extend in open dirs as far as radius including bomb pos
	// check if collision with any mortal object
	// clean up the carnage
	int	dir = -1;
	int	index = -1;
	int	x = static_cast<int>(this->bomb->position->vX);
	int	y = static_cast<int>(this->bomb->position->vY);

	int forwardX = x;
	int forwardY = y;

	this->bomb->state == DYING;

	this->bomb->blast.push_back( std::pair<int, int>(x, y));
	while (++dir < 4){
		while (++index < this->bombRadius){
			this->getForward(static_cast<eControls>(dir), &forwardX, &forwardY);
			if (!(this->isOpen(forwardX, forwardY)))
				if (this->isMortal(forwardX, forwardY) == 0) // issue with mortal
					break;
			this->bomb->blast.push_back( std::pair<int, int>(forwardX, forwardY));
		}
		index = -1;
		forwardX = x;
		forwardY = y;
	}

	// debug print bomb blast
	for (int i = 0; i < this->bomb->blast.size(); i++){
		std::cout << "blast coord: " << this->bomb->blast[i].first << ";" << this->bomb->blast[i].second << std::endl;
	}

	for (int j = 0; j < this->map.size(); j++){
		for (int i = 0; i < this->bomb->blast.size(); i++){
			if (this->map[j]->position->vX == this->bomb->blast[i].first && this->map[j]->position->vY == this->bomb->blast[i].second && this->map[j]->state == ALIVE && this->map[j]->mortal == 1){
				//std::cout << "dead coord: " << this->map[j]->position->vX << ";" << this->map[j]->position->vY << std::endl; // debug
				this->map[j]->state = DEAD;
			}
		}
	}
	for (int j = 0; j < this->enemies.size(); j++){
		for (int i = 0; i < this->bomb->blast.size(); i++){
			if (this->enemies[j]->destination->vX == this->bomb->blast[i].first && this->enemies[j]->destination->vY == this->bomb->blast[i].second && this->enemies[j]->state == ALIVE){
				this->enemies[j]->state = DEAD;
			}
		}
	}
	std::cout << "pre exit" << std::endl;

	// RENDER EXPLOSION // NEEDS TO BE MOVED AND PROLONGED
	for (int i = 0; i < this->bomb->blast.size(); i++){
		std::cout << "splode" << std::endl;
		this->engine->drawModel(WALL, (this->bomb->blast[i].first), (this->bomb->blast[i].second), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	}
	//exit(-1); // debug

	delete this->bomb; // test
	this->bomb = NULL;
	std::cout << "boom" << std::endl;
}