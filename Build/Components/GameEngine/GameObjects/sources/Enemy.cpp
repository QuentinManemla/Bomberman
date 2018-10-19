# include "../includes/Enemy.hpp"

Enemy::Enemy( eGameObjectType type, Vector3d *position ){
	this->position = position;
	this->destination = new Vector3d( this->position->vX, this->position->vY, this->position->vZ );
	this->eType = type;
	this->state = ALIVE;
	this->step = 0;
	this->currentDirection = static_cast<eControls>(rand() % 4); // set random start dir
	this->velocity = 2.0;
}

Enemy::Enemy(Enemy const & src) {}

Enemy	&Enemy::operator=(Enemy const &rhs) {}

Enemy::~Enemy( void ){

}