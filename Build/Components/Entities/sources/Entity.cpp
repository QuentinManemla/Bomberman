#include "../includes/Entity.hpp"

Entity::Entity( float posX, float posY, eType type ) : posX(posX), posY(posY), type(type){
	this->strType = "Entity";
	std::cout << this->strType << " constructed" << std::endl;
}

Entity::Entity( void ){
}

Entity::~Entity( void ){
	std::cout << this->strType << " destructed" << std::endl;
}

void		Entity::move(){
	std::cout << this->strType << " move" << std::endl;
}

void		Entity::die(){
	std::cout << this->strType << " die" << std::endl;
}
