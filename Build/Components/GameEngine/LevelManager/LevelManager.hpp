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
	LevelManager( int _level );
	LevelManager( int _level, int duration );
	LevelManager( void );
	~LevelManager( void );

	std::vector<GameObject *>	generateMap( void );
	void						pushObject( int type, int x, int y ); // may take level int in future;
	void						setDoor( void );
	void						setEnemies( void );
	void						encloseSafeZone( void );
	bool						isSafeZone(int x, int y);

	void						debugPrintMap( void ); // debug // test
	void						debugPrintEnemies( void ); // debug // test

	int									level;
	int									duration;
	std::vector<std::pair<int, int>>	openBlock; // changed from enemies
	std::vector<std::pair<int, int>>	enemies; // changed from enemies
	static int							walls;
	int									mapWidth;
	int									mapHeight;
	std::vector<GameObject *>			map; // map = vector of game objects // breakable walls can "contain" other objects // can have predetermined or drop based on rng
	int									numEnemies;

protected:

private:

};

#endif