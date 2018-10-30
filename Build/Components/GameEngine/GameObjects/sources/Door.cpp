# include "../includes/Door.hpp"

Door::Door( eGameObjectType type, Vector3d *position ){
	this->position = position;
	this->eType = type;
	this->state = ALIVE;
	this->mortal = 0;
}

Door::Door(Door const & src) {
	this->position = src.position;
}

Door &Door::operator=(Door const &rhs) {
	return *(new Door(rhs));
}

Door::~Door( void ){

}