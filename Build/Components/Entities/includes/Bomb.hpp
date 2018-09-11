#ifndef BOMB_HPP
# define BOMB_HPP

# include <pair>

class Bomb {
public:
	Bomb( float posX, float posY );
	Bomb( void );
	~Bomb( void );

	//std::pair<float, float> snapGrid( float posX, float posY );
	//std::vector<std::pair<float, float>> explode();

	float			fuseTime;
	int				radius;
	std::vector<std::pair<float, float>> totalPos;
	std::string		strType;

protected:

private:

};

#endif