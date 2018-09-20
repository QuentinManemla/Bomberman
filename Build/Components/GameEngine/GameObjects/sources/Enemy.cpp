# include "Enemy.hpp"

Enemy::Enemy( eGameObjectType type, Vector3d *position ){
	this->position = position;
	this->eType = type;
}

Enemy::~Enemy( void ){

}