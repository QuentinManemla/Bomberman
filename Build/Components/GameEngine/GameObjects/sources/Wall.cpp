# include "../includes/Wall.hpp"

Wall::Wall( eGameObjectType type, Vector3d *position ){
	this->strType = "Wall";
	this->position = position;
	this->eType = type;
	this->state = ALIVE;
	this->mortal = 1;
}

Wall::~Wall( void ){

}