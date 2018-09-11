# include "../includes/Bomb.hpp"

Bomb::Bomb( float posX, float posY ){
	this->strType = "Bomb";
	std::cout << this->strType << " constructed" << std::endl;
}

Bomb::Bomb( void ){

}

Bomb::~Bomb( void ){
	std::cout << this->strType << " destructed" << std::endl;
}

/*
std::pair<float, float> Bomb::snapGrid( float posX, float posY ){
	std::cout << this->strType << " snapGrid" << std::endl;
}

std::vector<std::pair<float, float>> Bomb::explode(){
	std::cout << this->strType << " explode" << std::endl;
}
*/