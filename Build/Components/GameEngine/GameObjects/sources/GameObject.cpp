#include "../includes/GameObject.hpp"

GameObject::GameObject( eGameObjectType type, Vector3d *position ){
	this->position = position;
	this->destination = new Vector3d( this->position->vX, this->position->vY, this->position->vZ );
	this->eType = type;
	this->state = ALIVE;
	this->step = 0;
}

GameObject::GameObject( void ){
}

GameObject::GameObject(GameObject const & src) {}

GameObject	&GameObject::operator=(const GameObject &rhs) {}

GameObject::~GameObject( void ){
	delete this->position;
}
