#include "../headers/Game.hpp"

Game::Game( void ){
	this->_EM = new EntityManager(); // new entity manager for new level? Or LevelManager to modify EntityManager?
	this->_win.create(sf::VideoMode(640, 480), "Bomberman", sf::Style::Close); // test // debug

}

Game::~Game( void ){
	delete this->_EM;
	this->_win.close(); // test // debug

}

void Game::gameloop( void ){
	int		quit = 0;
	int		ticks = -1;
	int		seconds = 0;

	while (!(quit)){
		ticks++;
		if (ticks % 32 == 0){
			std::cout << ticks / 32 << std::endl; // test // outputs seconds
		}
		if (ticks == 10 * 32) // test // debug // quits at 10 seconds
			quit++;
		//this.getKey();
		//this->_EM->update( this->key );
		//this.draw();
		usleep(31250); // for 32fps
	}
}

/*void	Game::getKey( void ){ // test // debug

}

void	Game::draw( void ){ // test // debug

}*/
