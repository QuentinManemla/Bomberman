#include "../includes/Bomb.hpp"

Bomb::Bomb( eGameObjectType type, Vector3d *position, float fuseTime ){
	this->position = position;
	//this->destination = new Vector3d( this->position->vX, this->position->vY, this->position->vZ );
	this->fuseTime = fuseTime;
	this->eType = type;
	this->state = ALIVE;
	this->step = 0;
}
Bomb::Bomb(Bomb const & src) {}
Bomb	&Bomb::operator=(Bomb const &rhs) {}
Bomb::~Bomb( void ){
}
