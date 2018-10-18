#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

//! enemy object
class Enemy : public GameObject{
public:
	Enemy( eGameObjectType type, Vector3d *position );
	~Enemy( void );

protected:

private:

};

#endif