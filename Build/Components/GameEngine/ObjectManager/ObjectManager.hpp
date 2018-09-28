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
	void		update(eControls key, int remainingTime);
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
	void		playerReset( void );
	void		ImmortalTick( void );
	void		processRemaingingTime( int remainingTime );
	void		levelProcess( int remainingTime );
	void		updatePlayerScore( int amount );
	int			allEnemiesDead( void );


	Engine						*engine;
	LevelManager				*LM;
	std::vector<GameObject *>	map;
	std::vector<GameObject *>	enemies;
	GameObject					*player;
	Bomb						*bomb;
	float						fuseTime;
	int							bombRadius;
	float						blastTime;
	float						playerImmortalTime;
	float						playerImmortalTicker;
	int							playerScore;
	bool						timeSpeedupFlag;
	Vector3d					*doorPos;

protected:

private:

};

#endif