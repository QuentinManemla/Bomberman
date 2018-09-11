#include "../includes/Enemy.hpp"

Enemy::Enemy( float posX, float posY, eType type) : posX(posX), posY(posY), type(type){
	this->strType = "Enemy";
	std::cout << this->strType << " constructed" << std::endl;
	// default values
	this->lives = 3;
	this->speed = 1; // arbitrary value for now
}

Enemy::~Enemy(){
	std::cout << this->strType << " destructed" << std::endl;
}