#ifndef WALL_HPP
# define WALL_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

class Wall : public GameObject{
public:
	Wall( eGameObjectType type, Vector3d *position );
	Wall(Wall const & src);
	Wall	&operator=(Wall const &rhs);
	~Wall( void );

protected:

private:

};

#endif