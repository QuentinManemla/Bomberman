#ifndef SOLIDWALL_HPP
# define SOLIDWALL_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

class SolidWall : public GameObject{
public:
	SolidWall( eGameObjectType type, Vector3d *position );
	SolidWall(SolidWall const & src);
	SolidWall	&operator=(SolidWall const &rhs);
	~SolidWall( void );

protected:

private:

};

#endif