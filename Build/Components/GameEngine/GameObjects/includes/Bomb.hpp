#ifndef BOMB_HPP
# define BOMB_HPP

# include "GameObject.hpp"
# include "../../Vector3d/Vector3d.hpp"

class Bomb : public GameObject {
public:
	Bomb( eGameObjectType type, Vector3d *position, float fuseTime );
	Bomb(Bomb const & src);
	Bomb	&operator=(Bomb const &rhs);
	~Bomb( void );

	float								fuseTime;
	std::vector<std::pair<int, int>>	blast;
protected:

private:

};

#endif