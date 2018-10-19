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

//! Base class of all game objects
class ObjectManager {
public:
	ObjectManager( Engine & engine ); // may need reference to playstate
	//! Initialize the variables when loading a game
	ObjectManager( Engine & engine, int level, int score, int retime ); // may need reference to playstate
	ObjectManager( void ); // may need reference to playstate
	~ObjectManager( void );


	//needs init() function
	//! Update the movements/actions of everything on the map, update the movements/action 
	//! of the player depending on the key passed into the function
	void		update(eControls key/*, int remainingTime*/);
	//! Draw the model of the objects occupying the map depending on their location
	void		render(void);
	/*! 
	 * Takes in a GameObject and the keypressed
	 * \n Check if the GameObject has finish moving yet, before taking in the input of a new direction
	 * \n Check if the requested direction is possible
	 * \n Call move to move to the direction requested
	 */
	void		requestMove(GameObject *actor, eControls key); // returns direction // or void and calls move directly
	//! Checks for if the coordinate is available
	int			isOpen(int x, int y);
	//! Returns a bool of death
	int			isMortal(int x, int y); // test
	//! Takes in a GameObject and an int
	//! /n Use function getVectorDifference and move accordingly
	void		move( GameObject *actor, int vectorDifference );
	//! Check if the position the GameObject is trying to access is available and move on to the position if it is
	void		requestEnemyMove( GameObject *actor );
	//! Check for the position of the GameObject and the destination of it, and check what's the difference
	int			getVectorDifference(GameObject *actor);
	float		getZStep( GameObject *actor );
	//! Place enemies onto the game map
	void		placeEnemies( void );
	//! Check if the GameObject is at the destination it tried to move to
	bool		isAtDestination( GameObject *actor);
	//! Update x and y to the next position
	void		getForward( eControls key , int *x, int *y);
	//! Choose a free direction to move in
	void		getOpenDirection( GameObject *actor );
	//! Randomly choose a free direction to move in
	void		getRandomOpenDirection( GameObject *actor );

	//! Place a bomb in at the destination of the player
	void		placeBomb( void );
	//! Check for anything breakable within its radius and kill all that can be destroyed render the explosion animation
	void		explode( void );
	void		checkEnemyCollision( void );
	//! Set player as dead when player dies
	void		playerDied( void );
	//! Check if the 2 vectors are the same
	int			isDestVectorEqual(Vector3d *first, Vector3d *second);
	//! Reset the player position when player dies
	void		playerReset( int penalize );
	//! Make player immortal the first few seconds when respawned
	void		ImmortalTick( void );
	//void		processRemaingingTime( int remainingTime );
	/*!
	 * Takes in the time remaining on the timer
	 * \n Check if all enemy is dead
	 * \n Check if the position of the player is equal to the position of the door
	 * \c If enemies are all dead, and the player is at the position of the door, proceed to the next level
	 */
	void		levelProcess( int remainingTime );
	//! Takes in an int representing the amount of points earned and add the amount onto the player score
	void		updatePlayerScore( int amount );
	//! Check if all enemies are dead
	int			allEnemiesDead( void );
	/*!
	 * Takes in an int value for which level you are at, 
	 * and a boolean value for whether or not you’ve succeeded in finishing up the stage
	 * determine if the stage has been completed successfully, or failed, set the state of the game accordingly
	 */
	void		initLevel( int level, bool success );
	//! Places the powerups into the x and y position given
	void		placePowerup( float x, float y);
	//! Check if the player position is at the same position as the powerup if it is, then the bomb radius increase by 1
	void		powerupCollision( void );




	Engine						*engine;
	LevelManager				*LM;
	std::vector<GameObject *>	map; // pointer or reference
	std::vector<GameObject *>	enemies; //!< list of all enemies
	std::vector<GameObject *>	powerups;//!< list of all powerups // new 
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