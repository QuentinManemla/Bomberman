# include "../includes/Door.hpp"

Door::Door( eGameObjectType type, Vector3d *position ){
	this->position = position;
	this->eType = type;
	this->state = ALIVE;
	this->mortal = 0;
}

Door::Door(Door const & src) {}

Door &Door::operator=(Door const &rhs) {}

Door::~Door( void ){

}