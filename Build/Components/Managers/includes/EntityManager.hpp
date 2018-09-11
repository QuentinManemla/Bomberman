#ifndef ENTITYMANAGER_HPP
# define ENTITYMANAGER_HPP

# include "../../Entities/includes/Entity.hpp"
# include "../../Entities/includes/Player.hpp"
# include "../../Entities/includes/Enemy.hpp"
# include "../../Entities/includes/Bomb.hpp"
# include "../../Entities/includes/enumEnemyType.hpp"

class EntityManager {
public:
	//EntityManager( config? )
	EntityManager( void );
	~EntityManager( void );

	//bool	checkCollision(float posX, float posY);
	//void	collisionManager( void );
	//void	draw( void );
	//void	moveCheck( eControls key ); // checks if requested move is possible 

	Player *player;
	//Enemy *enemy; // array
	//Bomb *bomb; // array or dynamic (if this line is implemented it will be the former)

protected:

private:

};

#endif