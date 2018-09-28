#include "LevelManager.hpp"
#include <iostream>

int LevelManager::level = 0;
//int LevelManager::enemies = 0;

// I think LevelManager should only come into existence when creating a level,
// then deleted. This way it can be reinitialized with the level value each time

LevelManager::LevelManager( int level ){
	srand(time(NULL));
	level = level;

	switch(level) {
		case(1):
			this->duration = 150; // test debug was 100
			this->numEnemies = 7; // get based on level
			break;
		case(2):
			this->duration = 140;
			this->numEnemies = 10; // get based on level
			break;
		case(3):
			this->duration = 130;
			this->numEnemies = 13; // get based on level
			break;
	}

	this->mapWidth = 13; // must be odd between 7 and 31
	this->mapHeight = 13; // must be odd between 7 and 31
	assert(this->mapWidth >= 7 && this->mapWidth <= 31 && this->mapHeight % 2 != 0);
	assert(this->mapHeight >= 7 && this->mapWidth <= 31 && this->mapWidth % 2 != 0);
	// enemies = this->mapWidth * this->mapHeight / 50 + (level * 2);
	std::cout << "LevelManager constructed" << std::endl; // debug
}

LevelManager::LevelManager( void ){

}

LevelManager::~LevelManager( void ){
	std::cout << "LevelManager destructed" << std::endl; // debug

}

std::vector<GameObject *>	LevelManager::generateMap( void ){
	// using 1d vector
	// fixed map size
	// abundance of enemies and breakable bricks depends on level
	// (total vector elements / y) + x
	// totalBlocks = x*y
	int w = this->mapWidth;
	int h = this->mapHeight;
	int block = 1;
	int type;
	int innerLine = 1;
	int	y = 1;
	int x = 1;
	int	solidCountDebug = 0;
	int	breakableCountDebug = 0;
	int	openCountDebug = 0;
	int	doorFlag = 0;

	for (int i = 0; i < (h * w); i++){ // i will increment from 0 to (TOTAL_BLOCKS - 1)
		type = 0;
		if (x == 1 || x == w || y == 1 || y == h){// If boarders: type = 1 (SolidWall)
			type = 1;
			block = 0;
		}
		else { // if not boarder
			// insert random objects here avoiding player spawn zone in top left corner
			if ((x == 2 && y <= 4) || (y == 2 && x <= 4)){// keeps player start area clear
				type = 5; // type 5 indicates safe zone where no blocks will spawn
			}
			else
				if (rand() % 3 == 1) // chance of spawning Wall on this coord
					type = 2;
			// end insert random object
			if (y != 1 && y != h){// generate SolidWall grid, leaving second and second last row open
				innerLine++;
				block++;
				if (block % 2 == 0 && innerLine % 2 == 0)
					type = 1;
			}
		}
		if (type == 1)
			solidCountDebug++;
		else if (type == 2)
			breakableCountDebug++;
		else if (type == 0)
			openCountDebug++;

		// std::cout << i << " type =" << type << "; totalline (x;y) = " << x << ";" << y << std::endl; // debug
		pushObject(type, x, y);
		x++;
		if (x == w + 1){
			x = 1;
			y++;
		}
	}
	std::cout << "solid = " << solidCountDebug << "\nopen = " << openCountDebug << "\nbreakable = " << breakableCountDebug << std::endl;
	setDoor();
	setEnemies();
	//this->debugPrintMap(); //debug
	//exit(-1); // debug
	return (this->map);
}

void	LevelManager::pushObject( int type, int x, int y ){ // may take level int in future;
	//std::cout << "pushObject" << " type =" << type << "; totalline (x;y) = " << x << ";" << y << std::endl;
	GameObject *object;
	switch (type){
		case 0:
			this->openBlock.push_back(pair<int, int>(x, y));
			return;
		case 1:
			object = (new SolidWall(SOLIDWALL, new Vector3d(x, y, 0)));
			break;
		case 2:
			object = (new Wall(WALL, new Vector3d(x, y, 0)));
			break;
		//case 3:
		//	this->enemies.push_back(pair<int, int>(x, y));
		//	return;
		case 4:
			object = (new Door(DOOR, new Vector3d(x, y, 0)));
			std::cout << "door = " << x << ";" << y << std::endl;
			break;
		case 5:
			return;
	};
	//std::cout << "object debug pre push" << object->strType << " " << object->position->vX << ";" << object->position->vY << std::endl; // debug
	this->map.push_back(object);
}

void	LevelManager::setDoor( void ){
	int	doorFlag = 0;
	GameObject *door;

	while (doorFlag == 0)
		for (int i = 0; i < this->map.size(); i++){
			if (doorFlag == 0){
				if (this->map[i]->eType == WALL){
					if (rand() % 50 == 0){
						door = new Door(DOOR, new Vector3d(this->map[i]->position->vX, this->map[i]->position->vY, this->map[i]->position->vZ));
						doorFlag = 1;
						this->map.push_back(door);
						std::cout << "Door placed at " << door->position->vX << ";" << door->position->vY << std::endl; // debug
					}
				}
			}
		}
}

void	LevelManager::setEnemies( void ){	
	while (this->numEnemies > 0){
		for (int i = 0; i < this->openBlock.size(); i++){
			if (rand() % 50 == 0){
				this->enemies.push_back(std::pair<int, int>(this->openBlock[i].first, this->openBlock[i].second));
				//std::cout << "openBlock popped at " << this->openBlock[i].first << ";" << this->openBlock[i].second << " : "<< i << std::endl; // debug
				this->numEnemies--;
				this->openBlock.erase(this->openBlock.begin() + i);
			}
			if (this->numEnemies == 0)
				break;
		}
	}
	//exit(-1);//debug
}


void	LevelManager::debugPrintMap( void ){ // debug // test
	std::cout << "total = " <<map.size() << std::endl;
	for (int i = 0; i < map.size(); i++){
		//std::cout << map[i]->strType << " = " << map[i]->position->vX << ";" << map[i]->position->vY << std::endl;
		std::cout << map[i]->eType;
		if (i % this->mapWidth == 0)
			std::cout << std::endl;
	}
}

void	LevelManager::debugPrintEnemies( void ){ // debug // test
	std::cout << "total = " << enemies.size() << std::endl;
	for (int i = 0; i < enemies.size(); i++){
		std::cout << this->enemies[i].first << ";" << this->enemies[i].second << std::endl;
	}
}