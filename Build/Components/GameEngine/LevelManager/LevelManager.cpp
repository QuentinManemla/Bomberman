#include "LevelManager.hpp"
#include <iostream>

int LevelManager::level = 0;
int LevelManager::enemies = 0;

// I think LevelManager should only come into existence when creating a level,
// then deleted. This way it can be reinitialized with the level value each time

LevelManager::LevelManager( int level ){
	srand(time(NULL));
	level = level;
	this->mapWidth = 13; // must be odd between 7 and 31
	this->mapHeight = 13; // must be odd between 7 and 31
	assert(this->mapWidth >= 7 && this->mapWidth <= 31 && this->mapHeight % 2 != 0);
	assert(this->mapHeight >= 7 && this->mapWidth <= 31 && this->mapWidth % 2 != 0);
	enemies = this->mapWidth * this->mapHeight / 50 + (level * 2);
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
	int x;
	int	solidCountDebug = 0;
	int	breakableCountDebug = 0;
	int	openCountDebug = 0;

	for (int i = 0; i <= h * w; i++){
		type = 0;
		if (((i % w == 1) || (i % w == 0)) || ((i <= w) || (i >= (h * w) - w))){
			type = 1;
			block = 0;
		}
		else{
			// insert random objects here
			if ((i > w + 4) && (i != w * 2 + 2) && (i != w * 3 + 2)){ // keeps player start area clear
				if (rand() % 3 == 1)
					type = 2;
			}
			else
				type = 5;
			// end insert random object
			if ((i >= (w * 2 - 1)) &&
			(i < (w * h - (w * 2) - 1))){
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
		y = ((i+1)/w) + 1;
		x = ((i+1)%w);
		pushObject(type, x, y);
		std::cout << i << " type =" << type << "; totalline (x;y) = " << x << ";" << y << std::endl;
	}
	this->testMap.pop_back();
	std::cout << "solid = " << solidCountDebug << "\nopen = " << openCountDebug << "\nbreakable = " << breakableCountDebug << std::endl;
	std::cout << "LevelManager end generateMap()" << std::endl; // debug
	return (this->testMap);
}

void	LevelManager::pushObject( int type, int x, int y ){ // may take level int in future;
	std::cout << "pushObject" << " type =" << type << "; totalline (x;y) = " << x << ";" << y << std::endl;
	GameObject *object;
	switch (type){
		case 1:
			object = (new SolidWall(SOLIDWALL, new Vector3d(x, y, 0)));
			break;
		case 2:
			object = (new Wall(WALL, new Vector3d(x, y, 0)));
			break;
		case 0:
			return;
		case 5:
			return;
	};
	std::cout << "object debug pre push" << object->strType << " " << object->position->vX << ";" << object->position->vY << std::endl; // debug
	this->testMap.push_back(object);
}

void	LevelManager::debugPrintMap( void ){ // debug // test
	std::cout << "total = " <<testMap.size() << std::endl;
	for (int i = 0; i < testMap.size(); i++){
		std::cout << testMap[i]->strType << " = " << testMap[i]->position->vX << ";" << testMap[i]->position->vY << std::endl;
	}
}