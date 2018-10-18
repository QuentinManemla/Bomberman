#ifndef POWERUP_HPP
# define POWERUP_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

//! powerup object
class Powerup : public GameObject{
public:
	Powerup( eGameObjectType type, Vector3d *position );
	~Powerup( void );

protected:

private:

};

#endif