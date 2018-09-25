# include "../includes/Player.hpp"

Player::Player( eGameObjectType type, Vector3d *position ) {
	this->position = position;
	this->eType = type;
	this->hitPoints = 3;
}

Player::~Player( void ){

}