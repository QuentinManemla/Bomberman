#ifndef DOOR_HPP
# define DOOR_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

class Door : public GameObject {
public:
	Door( eGameObjectType type, Vector3d *position );
	Door(Door const & src);
	Door	&operator=(Door const &rhs);
	~Door( void );

protected:

private:

};

#endif