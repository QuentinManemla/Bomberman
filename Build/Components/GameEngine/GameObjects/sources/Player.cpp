# include "../includes/Player.hpp"

Player::Player( eGameObjectType type, Vector3d *position ) {
	this->position = position;
	this->destination = new Vector3d( this->position->vX, this->position->vY, this->position->vZ );
	this->eType = type;
	this->hitPoints = 3;
	this->state = ALIVE;
	this->step = 0;
}

Player::~Player( void ){

}