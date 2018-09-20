#ifndef SOLIDWALL_HPP
# define SOLIDWALL_HPP

# include "GameObject.hpp"

class SolidWall : public GameObject{
public:
	SolidWall( eGameObjectType type, Vector3d *position );
	~SolidWall( void );

protected:

private:

};

#endif