#include "../headers/Player.hpp"

Player::Player(){
	this->posX = 0;
	this->posY = 0;
}

Player::~Player(){
	
}

int		Player::getX( void ){
	return this->posX;
}

int		Player::getY( void ){
	return this->posY;
}

void	Player::move( int	direction ){

}

void	Player::setPoints( int points ){
	this->points = points;
}
