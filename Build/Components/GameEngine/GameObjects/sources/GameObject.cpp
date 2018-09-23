#include "../includes/GameObject.hpp"

GameObject::GameObject( eGameObjectType type, Vector3d *position ){
	this->position = position;
	this->destination = new Vector3d( this->position->vX, this->position->vY, this->position->vZ );
	this->eType = type;
}

GameObject::GameObject( void ){
}

GameObject::~GameObject( void ){
	delete this->position;
}
