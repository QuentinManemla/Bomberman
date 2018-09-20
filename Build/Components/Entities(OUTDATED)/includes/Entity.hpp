#ifndef ENTITY_HPP
# define ENTITY_HPP

class Entity {
public:
	Entity( void );
	~Entity( void );

	void	move( float newX, float newY ); // or direction and delta time
	void	kill( void );
	void	birth( void );

	float	posX;
	float	posY;
	bool	active;
	float	speed;
	int		hp;

protected:

private:

};

#endif