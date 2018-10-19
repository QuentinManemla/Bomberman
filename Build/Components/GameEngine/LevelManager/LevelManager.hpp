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

//! The current levels info resides and updates here
class LevelManager {
public:
	LevelManager( int _level );
	LevelManager( int _level, int duration );
	LevelManager( void );
	~LevelManager( void );

	//! Creates the map and returns the list of all objects
	std::vector<GameObject *>	generateMap( void );
	//! Add object to map
	void						pushObject( int type, int x, int y ); // May take level int in future;
	void						setDoor( void ); //!< Creates the door for the level
	void						setEnemies( void ); //!< Sets enemies based on level
	//! Places breakable walls around the player, so no enemies can get to the player till he blast his way out
	void						encloseSafeZone( void ); 
	bool						isSafeZone(int x, int y); //!< Checks if you are in spawn

	void						debugPrintMap( void ); ///< // debug // test
	void						debugPrintEnemies( void ); ///< // debug // test

	int									level; //!< Current level
	int									duration; //!< How much time is left
	std::vector<std::pair<int, int>>	openBlock; //!< Changed from enemies
	std::vector<std::pair<int, int>>	enemies; //!< Changed from enemies
	static int							walls;
	int									mapWidth;
	int									mapHeight;
	std::vector<GameObject *>			map; //!< map = vector of GameObject 
											 //!< breakable walls can "contain" other objects
											 //!< can have predetermined or drop based on rng
	int									numEnemies; //!< The amount of enemies that are left

protected:

private:

};

#endif