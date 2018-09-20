#ifndef OBJECTMANAGER_HPP
# define OBJECTMANAGER_HPP

# include "ObjectManager.hpp"
# include "GameObject.hpp"
# include "enumControls.hpp"
# include "LevelManager.hpp"

class ObjectManager {
public:
	ObjectManager( void ); // may need reference to playstate
	~ObjectManager( void );

	void	update(eControls key, double deltaTime);
	void	render(void);
	void	canMove(GameObject *GameObject, eControls key); // returns direction // or void and calls move directly
	void	checkCollision( void );

	vector<GameObject *>	map;
	GameObject				*player;
	Bomb					*bomb;

protected:

private:

};

#endif