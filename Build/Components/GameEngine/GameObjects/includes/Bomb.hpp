#ifndef BOMB_HPP
# define BOMB_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

//! It is a bomb ... 1 2 3 BOOM
class Bomb : public GameObject {
public:
	//! Constructor that sets te defult fuse time taken from the param
	Bomb( eGameObjectType type, Vector3d *position, float fuseTime );
	~Bomb( void );

	float								fuseTime;
	std::vector<std::pair<int, int>>	blast;
protected:

private:

};

#endif