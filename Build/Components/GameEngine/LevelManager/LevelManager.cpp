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
			this->duration = 200;
			break;
		case(2):
			this->duration = 400;
			break;
		case(3):
			this->duration = 600;
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

		// if type == 0, random chance of spawning enemy
		// if type == 1, if flag1 not set, random chance of placing a door
		// make function to check if door is present, and how many enemies are present

		// RANDOM CHANCE FOR ENEMY
		if (type == 0){
			if (rand() % 10 == 0)
				type = 3; // test
		}

		//RANDOM CHANCE FOR DOOR // FIXXXXXXX
		if (type == 2){
			if (rand() % 10 == 0 && doorFlag < 1){
				doorFlag++;
				type = 4; // test
			}
		}

		// std::cout << i << " type =" << type << "; totalline (x;y) = " << x << ";" << y << std::endl; // debug
		pushObject(type, x, y);
		x++;
		if (x == w + 1){
			x = 1;
			y++;
		}
	}
	std::cout << "solid = " << solidCountDebug << "\nopen = " << openCountDebug << "\nbreakable = " << breakableCountDebug << std::endl;
	//this->debugPrintEnemies(); //debug
	//exit(-1); // debug
	return (this->testMap);
}

void	LevelManager::pushObject( int type, int x, int y ){ // may take level int in future;
	//std::cout << "pushObject" << " type =" << type << "; totalline (x;y) = " << x << ";" << y << std::endl;
	GameObject *object;
	switch (type){
		case 0:
			return;
		case 1:
			object = (new SolidWall(SOLIDWALL, new Vector3d(x, y, 0)));
			break;
		case 2:
			object = (new Wall(WALL, new Vector3d(x, y, 0)));
			break;
		case 3:
			this->enemies.push_back(pair<int, int>(x, y));
			return;
		case 4:
			object = (new Door(DOOR, new Vector3d(x, y, 0)));
			std::cout << "door = " << x << ";" << y << std::endl;
			break;
		case 5:
			return;
	};
	//std::cout << "object debug pre push" << object->strType << " " << object->position->vX << ";" << object->position->vY << std::endl; // debug
	this->testMap.push_back(object);
}

void	LevelManager::debugPrintMap( void ){ // debug // test
	std::cout << "total = " <<testMap.size() << std::endl;
	for (int i = 0; i < testMap.size(); i++){
		//std::cout << testMap[i]->strType << " = " << testMap[i]->position->vX << ";" << testMap[i]->position->vY << std::endl;
		std::cout << testMap[i]->eType;
		if (i & this->mapWidth == 0)
			std::cout << std::endl;
	}
}

void	LevelManager::debugPrintEnemies( void ){ // debug // test
	std::cout << "total = " << enemies.size() << std::endl;
	for (int i = 0; i < enemies.size(); i++){
		std::cout << this->enemies[i].first << ";" << this->enemies[i].second << std::endl;
	}
}