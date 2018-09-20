# include "Door.hpp"

Door::Door( eGameObjectType type, Vector3d *position ){
	this->position = position;
	this->eType = type;
}

Door::~Door( void ){

}