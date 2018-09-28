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

	void		update(eControls key, double deltaTime);
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

	Engine						*engine;
	LevelManager				*LM;
	std::vector<GameObject *>	map;
	std::vector<GameObject *>	enemies;
	GameObject					*player;
	Bomb						*bomb;
	float						fuseTime;
	int							bombRadius;

protected:

private:

};

#endif