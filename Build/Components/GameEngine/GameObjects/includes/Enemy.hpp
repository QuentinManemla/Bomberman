#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

class Enemy : public GameObject{
public:
	Enemy( eGameObjectType type, Vector3d *position );
	Enemy(Enemy const & src);
	Enemy	&operator=(Enemy const &rhs);
	~Enemy( void );

protected:

private:

};

#endif