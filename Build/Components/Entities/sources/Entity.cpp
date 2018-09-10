#include "../includes/Entity.hpp"

Entity::Entity( float posX, float posY, eType type ) : posX(posX), posY(posY), type(type){
	this->strType = "Entity";
	std::cout << this->strType << " constructed" << std::endl;
}

Entity::Entity( void ){
}

Entity::~Entity( void ){

}

void		Entity::move(){

}

void		Entity::die(){

}
