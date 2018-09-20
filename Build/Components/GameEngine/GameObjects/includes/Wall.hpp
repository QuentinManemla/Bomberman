#ifndef WALL_HPP
# define WALL_HPP

# include "GameObject.hpp"

class Wall : public GameObject{
public:
	Wall( eGameObjectType type, Vector3d *position );
	~Wall( void );

protected:

private:

};

#endif