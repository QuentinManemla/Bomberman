# include "../includes/Powerup.hpp"

Powerup::Powerup( eGameObjectType type, Vector3d *position ){
	this->strType = "Powerup";
	this->position = position;
	this->eType = type;
	this->state = ALIVE;
	this->mortal = 0;
}

Powerup::Powerup(Powerup const & src) {}

Powerup	&Powerup(Powerup const &rhs) {}

Powerup::~Powerup( void ){

}