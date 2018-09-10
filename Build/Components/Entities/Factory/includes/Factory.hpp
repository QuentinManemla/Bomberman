#ifndef FACTORY_HPP
# define FACTORY_HPP

# include "../../includes/Entity.hpp"
# include "../../includes/enumEntityType.hpp"
# include "../../Player/includes/enumPowertype.hpp"

class Gimme {
public:
	Gimme( void );
	~Gimme( void );
	Entity*		dat( eEntityType entityType ); // may change // Entity (player/enemy)
	Powerup*	dat( ePowerType powerType ); // may change // powerup

	// may need a header with constants such as "MAX_POWERUPS", etc

protected:

private:

};

#endif