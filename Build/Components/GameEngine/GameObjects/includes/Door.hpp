#ifndef DOOR_HPP
# define DOOR_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

//! a door class
class Door : public GameObject {
public:
	Door( eGameObjectType type, Vector3d *position );
	~Door( void );

protected:

private:

};

#endif