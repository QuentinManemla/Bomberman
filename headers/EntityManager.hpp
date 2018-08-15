#ifndef ENTITY_MANAGER_H
# define ENTITY_MANAGER_H

# include "Entity.hpp"
# include "Player.hpp"

class EntityManager {
public:
	EntityManager( void );
	~EntityManager( void );

protected:

private:
	Player *_player;
};

#endif