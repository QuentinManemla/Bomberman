# include "../includes/Wall.hpp"

Wall::Wall( eGameObjectType type, Vector3d *position ){
	this->strType = "Wall";
	this->position = position;
	this->eType = type;
	this->state = ALIVE;
}

Wall::~Wall( void ){

}