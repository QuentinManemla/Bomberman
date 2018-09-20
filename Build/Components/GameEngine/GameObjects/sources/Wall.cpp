# include "Wall.hpp"

Wall::Wall( eGameObjectType type, Vector3d *position ){
	this->strType = "Wall";
	this->position = position;
	this->eType = type;
}

Wall::~Wall( void ){

}