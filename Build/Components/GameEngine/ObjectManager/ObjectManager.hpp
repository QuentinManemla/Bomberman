#ifndef OBJECTMANAGER_HPP
# define OBJECTMANAGER_HPP

# include <vector>

# include "ObjectManager.hpp"
# include "../GameObjects/includes/GameObject.hpp"
# include "../GameObjects/includes/Bomb.hpp"
# include "../../Game/includes/enumControls.hpp"
# include "../LevelManager/LevelManager.hpp"

class ObjectManager {
public:
	ObjectManager( void ); // may need reference to playstate
	~ObjectManager( void );

	void	update(eControls key, double deltaTime);
	void	render(void);
	void	canMove(GameObject *GameObject, eControls key); // returns direction // or void and calls move directly
	void	checkCollision( void );

	std::vector<GameObject *>	map;
	GameObject				*player;
	Bomb					*bomb;

protected:

private:

};

#endif