# include "Player.hpp"

Player::Player( eGameObjectType type, Vector3d *position ){
	this->position = position;
	this->eType = type;
}

Player::~Player( void ){

}