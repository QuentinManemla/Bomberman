#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

class Player : public GameObject{
public:
	Player( eGameObjectType type, Vector3d *position );
	~Player( void );

protected:

private:

};

#endif