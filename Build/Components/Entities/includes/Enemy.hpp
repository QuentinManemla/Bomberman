#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "Entity.hpp"
//# include "enumEntityType.hpp"

class Enemy : public Entity {
public:
	Enemy( float posX, float posY, eType type);
	~Enemy( void );

protected:

private:

};

#endif