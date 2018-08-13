#ifndef ENTITY_H
# define ENTITY_H

class Entity {

public:

	int		getX( void );
	int		getY( void );
	int		move( int	direction );

	void	setPoints( int points );

protected:

private:
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