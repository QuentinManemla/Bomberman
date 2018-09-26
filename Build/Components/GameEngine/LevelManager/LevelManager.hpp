#ifndef LEVELMANAGER_HPP
# define LEVELMANAGER_HPP

# include <vector>
# include <iostream>
# include <cassert>

# include "LevelManager.hpp"
# include "../GameObjects/includes/GameObject.hpp"
# include "../GameObjects/includes/Door.hpp"
# include "../GameObjects/includes/Enemy.hpp"
# include "../GameObjects/includes/Player.hpp"
# include "../GameObjects/includes/Wall.hpp"
# include "../GameObjects/includes/SolidWall.hpp"

class LevelManager {
public:
	LevelManager( int level );
	LevelManager( void );
	~LevelManager( void );

	std::vector<GameObject *>	generateMap( void );
	void						pushObject( int type, int x, int y ); // may take level int in future;
	void						setDoor( void );

	void						debugPrintMap( void ); // debug // test
	void						debugPrintEnemies( void ); // debug // test

	static int					level;
	int							duration;
	std::vector<pair<int, int>>	enemies;
	static int					walls;
	int							mapWidth;
	int							mapHeight;
	std::vector<GameObject *>	testMap; // map = vector of game objects // breakable walls can "contain" other objects // can have predetermined or drop based on rng

protected:

private:

};

#endif