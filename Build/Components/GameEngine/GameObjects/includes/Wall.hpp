#ifndef WALL_HPP
# define WALL_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

//! wall object
class Wall : public GameObject{
public:
	Wall( eGameObjectType type, Vector3d *position );
	~Wall( void );

protected:

private:

};

#endif