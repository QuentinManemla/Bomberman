#ifndef OBJECTMANAGER_HPP
# define OBJECTMANAGER_HPP

# include <vector>

# include "ObjectManager.hpp"
# include "../GameObjects/includes/GameObject.hpp"
# include "../GameObjects/includes/Bomb.hpp"
# include "../../Game/includes/enumControls.hpp"
# include "LevelManager.hpp"
# include "../../Engine/includes/Engine.hpp"

class ObjectManager {
public:
	ObjectManager( Engine & engine );
	ObjectManager( void ); // may need reference to playstate
	~ObjectManager( void );

	void	update(eControls key, double deltaTime); // may get dT from engine
	void	render(void);
	void	canMove(GameObject *actor, eControls key); // returns direction // or void and calls move directly
	void	move( eControls key, GameObject *actor );
	void	checkCollision( void );

	Engine & engine;
	std::vector<GameObject *>	map;
	GameObject				*player;
	Bomb					*bomb;

protected:

private:

};

#endif