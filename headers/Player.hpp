#ifndef PLAYER_H
# define PLAYER_H

# include "Entity.hpp"

class Player: public Entity {
public:
	Player( void );
	~Player( void );
	int		getX( void );
	int		getY( void );
	void	move( int	direction );
	void	setPoints( int points );

protected:

private:

};

#endif