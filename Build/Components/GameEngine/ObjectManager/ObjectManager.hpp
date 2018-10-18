#ifndef OBJECTMANAGER_HPP
# define OBJECTMANAGER_HPP

# include <vector>

# include "ObjectManager.hpp"
# include "../GameObjects/includes/GameObject.hpp"
# include "../enums/enumGameObjectType.hpp"
# include "../GameObjects/includes/Bomb.hpp"
# include "../GameObjects/includes/Powerup.hpp"
# include "../../Game/includes/enumControls.hpp"
# include "../LevelManager/LevelManager.hpp"
# include "../../Engine/includes/Engine.hpp"

//! base class of all game objects
class ObjectManager {
public:
	ObjectManager( Engine & engine ); // may need reference to playstate
	//! initialize the variables when loading a game
	ObjectManager( Engine & engine, int level, int score, int retime ); // may need reference to playstate
	ObjectManager( void ); // may need reference to playstate
	~ObjectManager( void );


	//needs init() function
	//! update the movements/actions of everything on the map, update the movements/action 
	//! of the player depending on the key passed into the function
	void		update(eControls key/*, int remainingTime*/);
	//! draw the model of the objects occupying the map depending on their location
	void		render(void);
	/*! 
	 * takes in a GameObject and the keypressed
	 * check if the GameObject has finish moving yet, before taking in the input of a new direction
	 * check if the requested direction is possible
	 * call move to move to the direction requested
	 */
	void		requestMove(GameObject *actor, eControls key); // returns direction // or void and calls move directly
	//! checks for if the coordinate is available
	int			isOpen(int x, int y);
	//! returns a bool of death
	int			isMortal(int x, int y); // test
	//! takes in a GameObject and an int
	//! /n use function getVectorDifference and move accordingly
	void		move( GameObject *actor, int vectorDifference );
	//! check if the position the GameObject is trying to access is available and move on to the position if it is
	void		requestEnemyMove( GameObject *actor );
	//! check for the position of the GameObject and the destination of it, and check what's the difference
	int			getVectorDifference(GameObject *actor);
	float		getZStep( GameObject *actor );
	//! place enemies onto the game map
	void		placeEnemies( void );
	//! check if the GameObject is at the destination it tried to move to
	bool		isAtDestination( GameObject *actor);
	//! update x and y to the next position
	void		getForward( eControls key , int *x, int *y);
	//! choose a free direction to move in
	void		getOpenDirection( GameObject *actor );
	//! randomly choose a free direction to move in
	void		getRandomOpenDirection( GameObject *actor );

	void		placeBomb( void );
	void		explode( void );
	void		checkEnemyCollision( void );
	void		playerDied( void );
	int			isDestVectorEqual(Vector3d *first, Vector3d *second);
	void		playerReset( int penalize );
	void		ImmortalTick( void );
	//void		processRemaingingTime( int remainingTime );
	void		levelProcess( int remainingTime );
	void		updatePlayerScore( int amount );
	int			allEnemiesDead( void );
	void		initLevel( int level, bool success );
	void		placePowerup( float x, float y);
	void		powerupCollision( void );




	Engine						*engine;
	LevelManager				*LM;
	std::vector<GameObject *>	map; // pointer or reference
	std::vector<GameObject *>	enemies;
	std::vector<GameObject *>	powerups; // new
	GameObject					*player;
	Bomb						*bomb;
	const float					fuseTime;
	const float					playerImmortalTime;
	const int					powerupMax;
	int							powerupCount;
	int							bombRadius;
	float						blastTime;
	float						playerImmortalTicker;
	int							playerScore;
	bool						timeSpeedupFlag;

	std::chrono::steady_clock::time_point startTime;
	int				elapsedSec;
	int 			remainingTime;
	int 			displayTime;

protected:

private:

};

#endif