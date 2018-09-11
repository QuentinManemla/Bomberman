# include "../includes/EntityManager.hpp"

EntityManager::EntityManager( void ){
	std::cout << "EM constructed" << std::endl;
	this->player = new Player(0f, 0f, PLAYER);
}

EntityManager::~EntityManager( void ){
	std::cout << "EM destructed" << std::endl;
	delete this->player;
}
/*
bool	EntityManager::checkCollision(float posX, float posY){

}

void	EntityManager::collisionManager( void ){

}

void	EntityManager::draw( void ){

}

void	EntityManager::moveCheck( eControls key ){ // checks if requested move is possible

}
*/
