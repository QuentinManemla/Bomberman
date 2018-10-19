#ifndef SOLIDWALL_HPP
# define SOLIDWALL_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

//! solid wall GameObject
class SolidWall : public GameObject{
public:
	SolidWall( eGameObjectType type, Vector3d *position );
	~SolidWall( void );

protected:

private:

};

#endif