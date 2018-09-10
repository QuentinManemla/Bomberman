#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <string>
# include <iostream>

# include "../Powerups/includes/enumType.hpp"
# include "../Powerups/includes/Powerup.hpp"


class Entity {

public:
	// required methods
	Entity( void );
	Entity( float posX, float posY, eType type );
	~Entity( void );

	// member methods
	void		move();
	void		die();

	// member attributes
	int			lives;
	float		posX;
	float		posY;
	float		speed;
	Powerup		*powerup;
	eType		type;
	std::string	strType;

protected:

private:

};

#endif