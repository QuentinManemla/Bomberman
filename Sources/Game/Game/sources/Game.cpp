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
	int key = 0; // test // debug

	while (!(quit)){
		ticks++;
		if (ticks % 32 == 0){
			std::cout << ticks / 32 << std::endl; // test // outputs seconds
		}
		if ((key = this->getKey())){
			std::cout << key << std::endl;
		}
		//this->_EM->update( this->key );
		//this.draw();
		usleep(31250); // for 32fps
	}
}

int		Game::getKey( void ){ // test // debug
	sf::Event event;
	while (this->_win.pollEvent(event))
	{
		if (event.type == sf::Event::Closed){
			this->_win.close();
			exit(0);
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			return 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			return 2;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			return 3;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			return 4;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			exit(0);
	}
	return (0);
}

/*void	Game::draw( void ){ // test // debug

}*/
