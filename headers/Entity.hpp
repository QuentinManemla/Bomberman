#ifndef ENTITY_H
# define ENTITY_H

class Entity {

public:

	//virtual ~Entity( void);
	virtual int		getX( void ) = 0;
	virtual int		getY( void ) = 0;
	virtual void	move( int	direction ) = 0;
	virtual void	setPoints( int points ) = 0;
	int		posX;
	int		posY;
	//int		direction?
	//enum	Type;
	int		hitPoints;
	//enum	state;
	int		points;
	int		speedMultiplier;
	//<std::vector><Powerup> powerups // Vector of Classes.
};

#endif