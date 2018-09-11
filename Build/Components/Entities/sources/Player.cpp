#include "../includes/Player.hpp"

Player::Player( float posX, float posY, eType type) : posX(posX), posY(posY), type(type){
	this->strType = "Player";
	std::cout << this->strType << " constructed" << std::endl;
	// default values
	this->lives = 3;
	this->speed = 1; // arbitrary value for now
}

Player::~Player(){
	std::cout << this->strType << " destructed" << std::endl;
}