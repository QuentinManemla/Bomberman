#include "ObjectManager.hpp"

static int	fuse_time = 0;

ObjectManager::ObjectManager( Engine & engine ){
	this->engine = &engine;
	this->LM = new LevelManager(1); // may move this codeblock to a level init function to be available on call rather than this constructor
	this->map = this->LM->generateMap();
	this->player = new Player( PLAYER, new Vector3d(2, 2, 0.1f) );
	this->playerReset(); // start with temp immortality
	this->bomb = NULL;
	this->placeEnemies(); // 
	this->playerScore = 0;

	// INITS
	this->timeSpeedupFlag = 0;

	//SOME VALUES CHANGE BASED ON POWER UP: THESE ARE STARTING VALUES
	this->fuseTime = 1.5f;
	this->bombRadius = 2;
	this->playerImmortalTime = 2.0;
}

ObjectManager::~ObjectManager( void ){
	delete this->LM;
	delete this->player; // test
}

void	ObjectManager::update( eControls key, int remainingTime){
	// ADJUST VALUES BASED ON TIME
	this->processRemaingingTime(remainingTime);
	this->levelProcess( remainingTime );

	// PLACE BOMB
	if (key == FIRE){
		if (this->player->state == ALIVE)
			this->placeBomb(); // test
	}

	// CHECK PLAYER STATE // MIGHT NOT BE NEEDED
	if (this->player->hitPoints == 0)
		this->playerDied();

	// ENEMY - PLAYER COLLISION DETECTION
	for (int i = 0; i < this->enemies.size(); i++){
		if (isDestVectorEqual(this->player->destination, this->enemies[i]->destination) && this->enemies[i]->state == ALIVE && this->player->state == ALIVE){
			this->player->hitPoints -= 1; // move to 2;2 and become INVINCIBLE FOR A BIT 
			this->playerReset();
		}
	}

	// PLAYER MOVE
	if (this->player->state == ALIVE || this->player->state == DYING)
		requestMove(this->player, key);

	// ENEMY MOVE
	for (int i = 0; i < this->enemies.size(); i++){
		if (this->enemies[i]->state == ALIVE)
			requestEnemyMove(this->enemies[i]);
	}

	// INCREMENT BOMB FUSE
	if (this->bomb != NULL){
		this->bomb->fuseTime -= this->engine->_deltaTime;
		if (this->bomb->fuseTime < 0)
			if (this->bomb->state == DYING) {
				if (this->bomb->fuseTime < -0.1f) { // save as blastTime
					delete this->bomb;
					this->bomb = NULL;
				}
			}
			else{
				this->explode();
			}
	}
	// IF PLAYER = MORTAL IF PLAYER COLLISION WITH ENEMY, PLAYER--
	if (this->player->state == DYING)
		this->ImmortalTick();
}

void	ObjectManager::render(void){
	std::cout << "PLAYER POS: " << this->player->position->vX << ";" << this->player->position->vY << std::endl; // debug
	// std::cout << "PLR TRUNC : " << trunc(this->player->position->vX) << ";" << trunc(this->player->position->vY) << std::endl; // debug
	if (this->player->state == ALIVE)
		this->engine->drawModel(PLAYER, (this->player->position->vX), (this->player->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	else if (this->player->state == DYING)
		this->engine->drawModel(PLAYER, (this->player->position->vX), (this->player->position->vY), 0.02f);// draw goD mode model/
		
	for (int i = 0; i < this->enemies.size(); i++){
		if (this->enemies[i]->state == ALIVE)
			this->engine->drawModel(ENEMY, (this->enemies[i]->position->vX), (this->enemies[i]->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	}
	if (this->bomb != NULL) {
		if (this->bomb->state == ALIVE)
			this->engine->drawModel(BOMB, (this->bomb->position->vX), (this->bomb->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
		else if (this->bomb->state == DYING)
			for (int i = 0; i < this->bomb->blast.size(); i++){
				this->engine->drawModel(EXPLOSION, this->bomb->blast[i].first, this->bomb->blast[i].second , 0.02f);
			}
	} else {
		this->engine->explodeAnim = 0;
		this->engine->explodeMove = 0.02f;
	}
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
	float move = actor->velocity;
	switch (vectorDifference){
		case 1:
			move *= (((actor->position->vX * 10) / 10) > (actor->destination->vX * 10) / 10 ? -1.0f : 1.0f);
			if (((actor->position->vX * 10) / 10) == (actor->destination->vX * 10) / 10)
				move = 0;
			//if (abs(actor->position->vX - actor->destination->vX) > 0.09)// test // debug // WORK BUT MOVE TO PRIMARY CONDITION
				actor->position->vX += move * this->engine->_deltaTime;
			//actor->position->vZ = getZStep(actor);
			break;
		case 2:
			move *= (((actor->position->vY * 10) / 10) > (actor->destination->vY * 10) / 10 ? -1.0f : 1.0f);
			if (((actor->position->vY * 10) / 10) == (actor->destination->vY * 10) / 10)
				move = 0;
			//move = (actor->position->vY > actor->destination->vY ? -0.1 : 0.1);
			actor->position->vY += move * this->engine->_deltaTime;
			break;
		case 3:
			move *= (((actor->position->vZ * 10) / 10) > (actor->destination->vZ * 10) / 10 ? -1.0f : 1.0f);
			if (((actor->position->vZ * 10) / 10) == (actor->destination->vZ * 10) / 10)
				move = 0;
			//move = (actor->position->vZ > actor->destination->vZ ? -0.1 : 0.1);
			actor->position->vZ += move * this->engine->_deltaTime;
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
		if (x == this->bomb->position->vX && y == this->bomb->position->vY && this->bomb->state == ALIVE) // debug
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

void	ObjectManager::placeEnemies( void ){
	int x;
	int y;

	if (this->LM->enemies.size() > 0)
		for ( int i = 0; i < this->LM->enemies.size(); i++){
			x = this->LM->enemies[i].first;
			y = this->LM->enemies[i].second;
			this->enemies.push_back(new Enemy( ENEMY, new Vector3d(x, y, 0.1f) )); // test // debug
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
	this->engine->_SoundEngine.playSoundSource(this->engine->_SoundEngine._PlaceBomb, false);
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
	this->engine->_SoundEngine.playSoundSource(this->engine->_SoundEngine._Explode, false);
	this->engine->bombAnim = 0;
	this->engine->bombMove = 0.005f;
	int	dir = -1;
	int	index = -1;
	int	mortalDestroyed = 0;
	int	x = static_cast<int>(this->bomb->position->vX);
	int	y = static_cast<int>(this->bomb->position->vY);

	int forwardX = x;
	int forwardY = y;

	this->bomb->state == DYING;

	this->bomb->blast.push_back( std::pair<int, int>(x, y));
	while (++dir < 4){
		while (++index < this->bombRadius){
			this->getForward(static_cast<eControls>(dir), &forwardX, &forwardY);
			if (this->isOpen(forwardX, forwardY) == 0){
				if (this->isMortal(forwardX, forwardY) == 0) // issue with mortal
					break;
				else if (this->isMortal(forwardX, forwardY) == 1)
					mortalDestroyed++;
				else if (mortalDestroyed > 1)
					break;
			}
			this->bomb->blast.push_back( std::pair<int, int>(forwardX, forwardY));
			if (mortalDestroyed > 0)
				break;
		}
		mortalDestroyed = 0;
		index = -1;
		forwardX = x;
		forwardY = y;
	}

	// debug print bomb blast
	for (int i = 0; i < this->bomb->blast.size(); i++){
		std::cout << "blast coord: " << this->bomb->blast[i].first << ";" << this->bomb->blast[i].second << std::endl;
	}

	// DESTROY BREAKABLE BLOCKS IN BLAST
	for (int j = 0; j < this->map.size(); j++){
		for (int i = 0; i < this->bomb->blast.size(); i++){
			if (this->map[j]->position->vX == this->bomb->blast[i].first && this->map[j]->position->vY == this->bomb->blast[i].second && this->map[j]->state == ALIVE && this->map[j]->mortal == 1){
				this->map[j]->state = DEAD;
				this->updatePlayerScore(10);
				// DOOR TEST
				//if (this->map[j]->door == 1){
					// new Door gets map[j] pos,
					// delete this->map[j]
					// this->map[i] = door;
				//}
				// END DOOR TEST
			}
		}
	}
	// KILL ENEMIES IN BLAST
	for (int j = 0; j < this->enemies.size(); j++){
		for (int i = 0; i < this->bomb->blast.size(); i++){
			if (this->enemies[j]->destination->vX == this->bomb->blast[i].first && this->enemies[j]->destination->vY == this->bomb->blast[i].second && this->enemies[j]->state == ALIVE){
				this->enemies[j]->state = DEAD;
				this->updatePlayerScore(50); // score
			}
		}
	}
	// KILL PLAYER IN BLAST // REDUCE HP FIRST
	for (int i = 0; i < this->bomb->blast.size(); i++){
		if (this->player->destination->vX == this->bomb->blast[i].first && this->player->destination->vY == this->bomb->blast[i].second){
			this->player->hitPoints -= 1;
			this->playerReset();
			this->updatePlayerScore(-20); // score
		}
	}

	// RENDER EXPLOSION // NEEDS TO BE MOVED AND PROLONGED
	for (int i = 0; i < this->bomb->blast.size(); i++) {
		this->engine->drawModel(WALL, (this->bomb->blast[i].first), (this->bomb->blast[i].second), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	}

	this->bomb->state = DYING;
}

void	ObjectManager::playerDied( void ){
	//this->updatePlayerScore(-100); // score
	this->playerScore = -100;
	this->player->state = DEAD;
}

int		ObjectManager::isDestVectorEqual(Vector3d *first, Vector3d *second){
	if (trunc(first->vX) != trunc(second->vX))
		return (0);
	else if (trunc(first->vY) != trunc(second->vY))
		return (0);
	else if (trunc(first->vZ ) != trunc(second->vZ))
		return (0);
	return (1);
}

void	ObjectManager::playerReset( void ){
	this->updatePlayerScore(-10); // score
	this->player->position->vX = 2.0f;
	this->player->position->vY = 2.0f;
	this->player->destination->vX = 2.0f;
	this->player->destination->vY = 2.0f;
	this->player->state = DYING;
}

void	ObjectManager::ImmortalTick( void ){
	if (this->player->hitPoints < 1){
		this->playerDied();
		return;
	}
	if (this->playerImmortalTicker < this->playerImmortalTime)
		this->playerImmortalTicker += this->engine->_deltaTime;
	else{
		this->playerImmortalTicker = 0;
		this->player->state = ALIVE;
	}
}

void	ObjectManager::processRemaingingTime( int remainingTime ){
	std::cout << "remaining time: " << remainingTime << std::endl; // debug
	if (remainingTime == 0)
		;//end level fail

	if (remainingTime < 20 && this->timeSpeedupFlag == 0){ // enemies speed up when time drops below 20 seconds remaining
		for (int i = 0; i < this->enemies.size(); i++){
			this->enemies[i]->velocity += 2.0f;
			this->timeSpeedupFlag = 1;
		}
	}
}


//void	ObjectManager::LevelEnd(/*stuff probably*/){
//	
//}

// in level manager
// certain wall gets door = true attribute
// if a wall dies and door is true, spawn door object
// door object has own properties

// Level transition:
// Level complete! continue to level X
// GO!
// save
// quit to menu

void	ObjectManager::updatePlayerScore( int amount ){
	this->playerScore += amount;
}

int		ObjectManager::allEnemiesDead( void ){
	for (int i = 0; i < this->enemies.size(); i++){
		if (this->enemies[i]->state == ALIVE)
			return (1);
	}
	return (0);
}

void	ObjectManager::levelProcess( int remainingTime ){
	// check time and adjust enemy speed
	// check if player collide with door
		// check if all enemies dead
		// if true then end level and initiate next one if there is one (endlevel(success))
}
