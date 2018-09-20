#include "GameObject.hpp"

GameObject::GameObject( eGameObjectType type, Vector3d *position ){
	this->position = position;
	this->eType = type;
}

GameObject::GameObject( void ){
}

GameObject::~GameObject( void ){
	delete this->position;
}
