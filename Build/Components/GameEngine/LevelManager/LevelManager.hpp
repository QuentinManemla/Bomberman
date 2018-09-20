#ifndef LEVELMANAGER_HPP
# define LEVELMANAGER_HPP

# include <vector>
# include <iostream>
# include <cassert>

# include "LevelManager.hpp"
# include "GameObject.hpp"
# include "Door.hpp"
# include "Enemy.hpp"
# include "Player.hpp"
# include "Wall.hpp"
# include "SolidWall.hpp"

class LevelManager {
public:
	LevelManager( int level );
	LevelManager( void );
	~LevelManager( void );

	std::vector<GameObject *>	generateMap( void );
	void						pushObject( int type, int x, int y ); // may take level int in future;

	void						debugPrintMap( void ); // debug // test

	static int					level;
	static int					enemies;
	static int					walls;
	int							mapWidth;
	int							mapHeight;
	std::vector<GameObject *>	testMap; // map = vector of game objects // breakable walls can "contain" other objects // can have predetermined or drop based on rng

protected:

private:

};

#endif