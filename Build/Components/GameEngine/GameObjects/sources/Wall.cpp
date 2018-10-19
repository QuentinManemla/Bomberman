# include "../includes/Wall.hpp"

Wall::Wall( eGameObjectType type, Vector3d *position ){
	this->strType = "Wall";
	this->position = position;
	this->eType = type;
	this->state = ALIVE;
	this->mortal = 1;
}

Wall::Wall(Wall const & src) {
	this->position = src.position;
}

Wall	&Wall::operator=(Wall const &rhs) {
	return (new Wall(rhs));
}

Wall::~Wall( void ){

}