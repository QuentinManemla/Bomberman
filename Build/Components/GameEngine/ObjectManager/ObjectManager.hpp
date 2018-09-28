#ifndef OBJECTMANAGER_HPP
# define OBJECTMANAGER_HPP

# include <vector>

# include "ObjectManager.hpp"
# include "../GameObjects/includes/GameObject.hpp"
# include "../enums/enumGameObjectType.hpp"
# include "../GameObjects/includes/Bomb.hpp"
# include "../../Game/includes/enumControls.hpp"
# include "../LevelManager/LevelManager.hpp"
# include "../../Engine/includes/Engine.hpp"

class ObjectManager {
public:
	ObjectManager( Engine & engine ); // may need reference to playstate
	ObjectManager( void ); // may need reference to playstate
	~ObjectManager( void );


	//needs init() function
	void		update(eControls key/*, int remainingTime*/);
	void		render(void);
	void		requestMove(GameObject *actor, eControls key); // returns direction // or void and calls move directly
	int			isOpen(int x, int y);
	int			isMortal(int x, int y); // test
	void		move( GameObject *actor, int vectorDifference );
	void		requestEnemyMove( GameObject *actor );
	int			getVectorDifference(GameObject *actor);
	float		getZStep( GameObject *actor );
	void		placeEnemies( void );
	bool		isAtDestination( GameObject *actor);
	void		getForward( eControls key , int *x, int *y);
	void		getOpenDirection( GameObject *actor );
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
	Vector3d					*doorPos;
	int							level;

	std::chrono::steady_clock::time_point startTime;
	int				elapsedSec;
	int 			remainingTime;
	int 			displayTime;

protected:

private:

};

#endif