#include "../includes/LevelManager.hpp"

LevelManager::LevelManager( void ){
	std::cout << "LM constructed" << std::endl;
	this->mapMax = 11;
	// NOTE:
	/*Don't need map object. Just render objects on the same plane based on
	  their positions. Random generation will work with special cases and
	  bounds of the map size, but will be in their own respective arrays*/
}

LevelManager::~LevelManager( void ){
	std::cout << "LM destructed" << std::endl;
}

void	LevelManager::generateMap( void ){

}

void	LevelManager::validMap(){

}

void	LevelManager::placeEnemies( void ){

}

void	LevelManager::placePowerups( void ){

}

void	LevelManager::placeDoor( void ){

}
