#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Entity.hpp"
//# include "enumEntityType.hpp"

class Player : public Entity {
public:
	Player( float posX, float posY, eType type);
	~Player( void );

protected:

private:

};

#endif