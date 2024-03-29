#include "ObjectManager.hpp"

// static int	fuse_time = 0;

ObjectManager::ObjectManager( Engine & engine ) : fuseTime(1.5f), playerImmortalTime(3.0f), powerupMax(3){
	this->engine = &engine;
	this->LM = new LevelManager(1); // may move this codeblock to a level init function to be available on call rather than this constructor
	this->player = new Player( PLAYER, new Vector3d(2, 2, 0.1f) );
	this->map = this->LM->generateMap();
	this->playerReset(0); // start with temp immortality
	this->placeEnemies(); //
	this->playerScore = 0;
	this->blastTime = -0.1f;

	// INITS
	this->powerupCount = 0;
	this->startTime = std::chrono::steady_clock::now();
	this->bomb = NULL;
	this->timeSpeedupFlag = 0;
	this->playerImmortalTicker = 0;
	this->engine->_SoundEngine.playSoundSource(this->engine->_SoundEngine._Play, true);
	this->engine->backgroundTexture("Assets/Textures/stone-wall.jpg");

	//SOME VALUES CHANGE BASED ON POWER UP: THESE ARE STARTING VALUES
	this->bombRadius = 1;
}

ObjectManager::ObjectManager( Engine & engine, int level, int score, int retime ) : fuseTime(1.5f), playerImmortalTime(3.0f), powerupMax(3){
	this->engine = &engine;
	this->LM = new LevelManager(level); // may move this codeblock to a level init function to be available on call rather than this constructor
	this->player = new Player( PLAYER, new Vector3d(2, 2, 0.1f) );
	this->map = this->LM->generateMap();
	this->playerReset(0); // start with temp immortality
	this->placeEnemies(); //
	this->playerScore = score;
	this->blastTime = -0.1f;
	this->remainingTime = retime;

	// INITS
	this->powerupCount = 0;
	this->startTime = std::chrono::steady_clock::now();
	this->bomb = NULL;
	this->timeSpeedupFlag = 0;
	this->playerImmortalTicker = 0;

	this->engine->_SoundEngine.stopSound();
	switch(level) {
		case 1:
			this->engine->backgroundTexture("Assets/Textures/stone-wall.jpg");
			this->engine->_SoundEngine.playSoundSource(this->engine->_SoundEngine._Play, true);
			break;
		case 2:
			this->engine->backgroundTexture("Assets/Textures/brick-floor.jpg");
			this->engine->_SoundEngine.playSoundSource(this->engine->_SoundEngine._Play2, true);
			break;
		case 3:
			this->engine->backgroundTexture("Assets/Textures/stone2-wall.jpg");
			this->engine->_SoundEngine.playSoundSource(this->engine->_SoundEngine._Play3, true);
			break;
		default:
			this->engine->backgroundTexture("Assets/Textures/stone-wall.jpg");
			this->engine->_SoundEngine.playSoundSource(this->engine->_SoundEngine._Play, true);
			break;
	}
	//SOME VALUES CHANGE BASED ON POWER UP: THESE ARE STARTING VALUES
	//this->fuseTime = 1.5f;
	this->bombRadius = 1;
	//this->playerImmortalTime = 3.0;
}

ObjectManager::ObjectManager(ObjectManager const & src): fuseTime(1.5f), playerImmortalTime(3.0f), powerupMax(3) {
	this->timeSpeedupFlag = src.timeSpeedupFlag;
}

ObjectManager	&ObjectManager::operator=(ObjectManager const &rhs) {
	return *(new ObjectManager(rhs));
}

ObjectManager::~ObjectManager( void ){
	delete this->LM;
	delete this->player; // test
}

void	ObjectManager::update( eControls key/*, int remainingTime*/){

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	this->elapsedSec = std::chrono::duration_cast<std::chrono::seconds>(end - this->startTime).count();
	this->remainingTime = this->displayTime = this->LM->duration - this->elapsedSec;
	if (this->remainingTime < 0)
		this->displayTime = 0;

	/** UPDATE SAVE VALUES **/
	this->engine->_Save.health = this->player->hitPoints;
	this->engine->_Save.level = this->LM->level;
	this->engine->_Save.points = this->playerScore;
	this->engine->_Save.remainingTime = this->remainingTime;

	// ADJUST VALUES BASED ON TIME
	//this->processRemaingingTime(remainingTime);
	this->levelProcess( this->remainingTime );

	// PLACE BOMB
	if (key == FIRE){
		if (this->player->state == ALIVE)
			this->placeBomb(); // test
	}

	// CHECK PLAYER STATE // MIGHT NOT BE NEEDED
	if (this->player->hitPoints == 0)
		this->playerDied();

	// ENEMY - PLAYER COLLISION DETECTION
	for (unsigned long i = 0; i < this->enemies.size(); i++){
		if (isDestVectorEqual(this->player->destination, this->enemies[i]->destination) && this->enemies[i]->state == ALIVE && this->player->state == ALIVE){
			this->player->hitPoints -= 1; // move to 2;2 and become INVINCIBLE FOR A BIT 
			this->playerReset(1);
		}
	}

	// PLAYER MOVE
	if (this->player->state == ALIVE || this->player->state == DYING){
		if (this->player->state == DYING)
			this->ImmortalTick();
		if (this->playerImmortalTicker > 1.0f || this->playerImmortalTicker == 0)
			requestMove(this->player, key);
	}

	// ENEMY MOVE
	for (unsigned long i = 0; i < this->enemies.size(); i++){
		if (this->enemies[i]->state == ALIVE)
			requestEnemyMove(this->enemies[i]);
	}

	// INCREMENT BOMB FUSE
	if (this->bomb != NULL){
		this->bomb->fuseTime -= this->engine->_deltaTime;
		if (this->bomb->fuseTime < 0){
			if (this->bomb->state == DYING) {
				if (this->bomb->fuseTime < this->blastTime) { // save as blastTime
					delete this->bomb;
					this->bomb = NULL;
				}
			}
			else{
				this->explode();
			}
		}
	}
	// IF PLAYER = MORTAL IF PLAYER COLLISION WITH ENEMY, PLAYER--
	if (this->player->state == DYING)
		this->ImmortalTick();

	// CHECK POWERUP COLLISION
	this->powerupCollision();
}

void	ObjectManager::render(void){
	std::cout << "PLAYER POS: " << this->player->position->vX << ";" << this->player->position->vY << std::endl; // debug
	// std::cout << "PLR TRUNC : " << trunc(this->player->position->vX) << ";" << trunc(this->player->position->vY) << std::endl; // debug

	// RENDER PLAYER
	if (this->player->state == ALIVE)
		this->engine->drawModel(PLAYER, (this->player->position->vX), (this->player->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	else if (this->player->state == DYING)
		this->engine->drawModel(PLAYER, (this->player->position->vX), (this->player->position->vY), 0.02f);// draw goD mode model/

	// RENDER ENEMIES
	for (unsigned long i = 0; i < this->enemies.size(); i++){
		if (this->enemies[i]->state == ALIVE)
			this->engine->drawModel(ENEMY, (this->enemies[i]->position->vX), (this->enemies[i]->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	}

	// RENDER POWERUP
	for (unsigned long i = 0; i < this->powerups.size(); i++){
		if (this->powerups[i]->state == ALIVE)
			this->engine->drawModel(POWERUP, (this->powerups[i]->position->vX), (this->powerups[i]->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	}

	// RENDER BOMB
	if (this->bomb != NULL) {
		if (this->bomb->state == ALIVE)
			this->engine->drawModel(BOMB, (this->bomb->position->vX), (this->bomb->position->vY), 0.02f);//this->player->position->vZ); // moved math to drawModel()
		else if (this->bomb->state == DYING)
			for (unsigned long i = 0; i < this->bomb->blast.size(); i++){
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
	for (unsigned long i = 0; i < this->map.size(); i++){
		if (this->map[i]->position->vX == x && this->map[i]->position->vY == y){
			if (this->map[i]->state == ALIVE)
				return (0);
			else
				return (1);
		}
	}
	return (1);
}

int		ObjectManager::isMortal(int x, int y){
	for (unsigned long i = 0; i < this->map.size(); i++){
		if (this->map[i]->position->vX == x && this->map[i]->position->vY == y){
			if (this->map[i]->mortal == 1)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

void	ObjectManager::requestEnemyMove( GameObject *actor ){
	int x = actor->position->vX;
	int y = actor->position->vY;

	int forwardX = x;
	int forwardY = y;

	int vectorDifference = 0;

	if ((vectorDifference = this->getVectorDifference(actor)) == 0){
		if (rand() % 5 == 0)
			getOpenDirection(actor);

			//getRandomOpenDirection(actor); // randomly change direction
	}

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
		for ( unsigned long i = 0; i < this->LM->enemies.size(); i++){
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
		default:
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
		start = (start + 1) % 4;
	}
	actor->stuck = 1;
}

void	ObjectManager::getRandomOpenDirection( GameObject *actor ){

	int	newDirection = 0;
	int	tries = 0;

	int	x = actor->position->vX;
	int	y = actor->position->vY;

	// rand to decide + or -
	if (rand() % 2 == 0)
		newDirection = static_cast<int>(actor->currentDirection) + 1;
	else
		newDirection = static_cast<int>(actor->currentDirection) - 1;
	// if actor currentDirection
	while (tries < 2){
		switch (newDirection){
			case 0:
				if (isOpen(x - 1, y) && newDirection != (actor->currentDirection + 2) % 4){
					std::cout << "return_left" << std::endl;
					actor->currentDirection = LEFT;
					return;
				}
			case 1:
				if (isOpen(x, y - 1) && newDirection != (actor->currentDirection + 2) % 4){
					std::cout << "return_up" << std::endl;
					actor->currentDirection = UP;
					return;
				}
			case 2:
				if (isOpen(x + 1, y) && newDirection != (actor->currentDirection + 2) % 4){
					std::cout << "return_right" << std::endl;
					actor->currentDirection = RIGHT;
					return;
				}
			case 3:
				if (isOpen(x, y + 1) && newDirection != (actor->currentDirection + 2) % 4){
					std::cout << "return_down" << std::endl;
					actor->currentDirection = DOWN;
					return;
				}
		}
		newDirection += 2;
		newDirection %= 4;
		tries++;
	}

/*
	int	start = (rand() % 4);
	int	tries = 3;

	int	x = actor->position->vX;
	int	y = actor->position->vY;

	actor->stuck = 0;
	while (tries-- != 0){
		if (start == (static_cast<int>(actor->currentDirection) + 2) % 4){
			start++;
			start %= 4;
		}
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
	*/
}


void	ObjectManager::placeBomb( void ){
	// check for bomb related powerup and then change bomb params accordingly
	if (this->bomb == NULL){
		this->engine->_SoundEngine.playSoundSource(this->engine->_SoundEngine._PlaceBomb, false);
		this->bomb = new Bomb(BOMB, new Vector3d(this->player->destination->vX, this->player->destination->vY, this->player->destination->vZ), this->fuseTime); // params subject to powerup
	}
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

	// this->bomb->state == DYING;

	this->bomb->blast.push_back( std::pair<int, int>(x, y));
	while (++dir < 4){
		while (++index < this->bombRadius){
			this->getForward(static_cast<eControls>(dir), &forwardX, &forwardY);
			if (this->isOpen(forwardX, forwardY) == 0){
				if (this->isMortal(forwardX, forwardY) == 0)
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
	for (unsigned long i = 0; i < this->bomb->blast.size(); i++){
		std::cout << "blast coord: " << this->bomb->blast[i].first << ";" << this->bomb->blast[i].second << std::endl;
	}

	// DESTROY BREAKABLE BLOCKS IN BLAST
	for (unsigned long j = 0; j < this->map.size(); j++){
		for (unsigned long i = 0; i < this->bomb->blast.size(); i++){
			if (this->map[j]->position->vX == this->bomb->blast[i].first && this->map[j]->position->vY == this->bomb->blast[i].second && this->map[j]->state == ALIVE && this->map[j]->mortal == 1){
				this->map[j]->state = DEAD;
				this->updatePlayerScore(10);
				this->placePowerup(this->map[j]->position->vX, this->map[j]->position->vY);
			}
		}
	}
	// KILL ENEMIES IN BLAST
	for (unsigned long j = 0; j < this->enemies.size(); j++){
		for (unsigned long i = 0; i < this->bomb->blast.size(); i++){
			if (this->enemies[j]->destination->vX == this->bomb->blast[i].first && this->enemies[j]->destination->vY == this->bomb->blast[i].second && this->enemies[j]->state == ALIVE){
				this->enemies[j]->state = DEAD;
				this->updatePlayerScore(50); // score
			}
		}
	}

	// REDUCE POINTS FOR BOMBING DOOR
	// copy loop from levelProcess to check if bomb blast hits door

	// KILL PLAYER IN BLAST // REDUCE HP FIRST
	for (unsigned long i = 0; i < this->bomb->blast.size(); i++){
		if (this->player->destination->vX == this->bomb->blast[i].first && this->player->destination->vY == this->bomb->blast[i].second){
			this->player->hitPoints -= 1;
			this->playerReset(1);
			this->updatePlayerScore(-20); // score
		}
	}

	// RENDER EXPLOSION // NEEDS TO BE MOVED AND PROLONGED
	for (unsigned long i = 0; i < this->bomb->blast.size(); i++) {
		this->engine->drawModel(WALL, (this->bomb->blast[i].first), (this->bomb->blast[i].second), 0.02f);//this->player->position->vZ); // moved math to drawModel()
	}

	this->bomb->state = DYING;
}

void	ObjectManager::playerDied( void ){
	//this->updatePlayerScore(-100); // score
	this->playerScore = -100;
	this->player->state = DEAD;
	std::cout << "initLevel player died: 414" << std::endl; // debug
	this->initLevel(1, 0); // fail
	return;
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

void	ObjectManager::playerReset( int penalize ){
	if (penalize == 1)
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
/*
void	ObjectManager::processRemaingingTime( int remainingTime ){
	std::cout << "remaining time: " << remainingTime << std::endl; // debug
	if (remainingTime == 0){
		this->initLevel(2, 1);//end level fail



}
*/

void	ObjectManager::initLevel( int level, bool success ){
	delete (this->LM);
	std::cout << "delete lm" << std::endl;
	if (this->bomb != NULL) {
		delete this->bomb;
		this->bomb = NULL;
	}

	if (level > 4)
		std::cout << "Huston we have a problem"; //I don't even know

	std::cout << "pre success" << std::endl;
	if (success){
		//win screen (continue, save, quit without saving)
		// this->LM = new LevelManager(2);
		// this->map = this->LM->generateMap();
		// this->startTime = std::chrono::steady_clock::now();
		// this->player->hitPoints++;
		// this->powerupCount = 0;
		// this->timeSpeedupFlag = 0;
		// this->playerReset(0);
		// this->placeEnemies();
		this->engine->_Camera.init(glm::vec3(0.48f, -1.1f, 2.7f));
		this->engine->state = SUCCESS;
		std::cout << "success" << std::endl;
	}
	else{
		std::cout << "fail" << std::endl;
		this->engine->_Camera.init(glm::vec3(0.48f, -1.1f, 2.7f));
		this->engine->state = FAIL;
		// exit(-1);//lose screen (restart level, quit to menu)
	}
	std::cout << "get here?" << std::endl;//debug
}

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
	for (unsigned long i = 0; i < this->enemies.size(); i++){
		if (this->enemies[i]->state == ALIVE)
			return (0);
	}
	return (1);
}

void	ObjectManager::levelProcess( int remainingTime ){
	// check time and adjust enemy speed
	// check if player collide with door
		// check if all enemies dead
		// if true then end level and initiate next one if there is one (endlevel(success))

	//if (remainingTime < 20 && this->timeSpeedupFlag == 0){ // enemies speed up when time drops below 20 seconds remaining
	//	for (int i = 0; i < this->enemies.size(); i++){
	//		this->enemies[i]->velocity += 2.0f;
	//		this->timeSpeedupFlag = 1;
	//	}
	//}

	if (allEnemiesDead() == 1)
		std::cout << "enemies dead!" << std::endl;
	else
		std::cout << "still enemies!" << std::endl;

	if (isDestVectorEqual(this->player->position, this->player->destination)){
		if (isDestVectorEqual(this->player->destination, this->map[this->map.size() - 1]->position) && this->allEnemiesDead() == 1){
			this->updatePlayerScore(remainingTime); // test // debug 1000
			std::cout << "initLevel entered door: 529" << std::endl; // debug
			this->initLevel(2, 1);//end level success
			return;
			//exit(-1);//endlevel(success)
		}
	}

	if (this->displayTime == 0){
		//exit(-1);//end level fail
		std::cout << "initLevel time up: 538" << std::endl; // debug
		this->initLevel(2, 0);//end level fail
		return;
	}

	if (this->displayTime < 50 && this->timeSpeedupFlag == 0){ // enemies speed up when time drops below 20 seconds remaining
		for (unsigned long i = 0; i < this->enemies.size(); i++){
			this->enemies[i]->velocity += 1.0f;
			this->timeSpeedupFlag = 1;
		}
	}
	std::cout << "remaining time: " << this->displayTime << std::endl; // debug
	std::cout << "timeflag: " << this->timeSpeedupFlag << std::endl; // debug
}

void	ObjectManager::placePowerup( float x, float y){
	if (this->powerupCount < this->powerupMax){
		if (rand() % 10 == 0){
			this->powerups.push_back(new Powerup(POWERUP, new Vector3d(x, y, 0.1f)));
			this->powerupCount++;
		}
	}
}

void	ObjectManager::powerupCollision( void ){
	for (unsigned long i = 0; i < this->powerups.size(); i++){
		if (this->isDestVectorEqual(this->player->position, this->powerups[i]->position) == 1 && this->powerups[i]->state == ALIVE){
			this->bombRadius++;
			this->powerups[i]->state = DEAD;
			break;
		}
	}
}

// TIME MANAGEMENT ACROSS LEVELS AND PAUSE NEEDS FIXING