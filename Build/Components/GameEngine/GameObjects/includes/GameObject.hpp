#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include <string>
# include <vector>

# include "../../enums/enumGameObjectState.hpp"
# include "../../enums/enumGameObjectType.hpp"
//# include "Enemy.hpp"
//# include "Door.hpp"
//# include "Bomb.hpp"
//# include "Player.hpp"
//# include "SolidWall.hpp"
//# include "Wall.hpp"
# include "../../Vector3d/Vector3d.hpp"
# include "../../../Engine/includes/Engine.hpp"

//# include "Door.hpp"
//# include "Enemy.hpp"
//# include "Player.hpp"
//# include "Wall.hpp"


class GameObject {
public:
	GameObject( eGameObjectType type, Vector3d *position );
	GameObject( void );
	GameObject(GameObject const & src);
	GameObject	&operator=(const GameObject &rhs);
	~GameObject( void );

	//addComponent
	//getComponent

	std::string				modelPath;
	std::string				spritePath;
	Vector3d				*position;
	Vector3d				*destination;
	int						step;
	float					velocity;
	eGameObjectState		state;
	eGameObjectType			eType;
	std::string				strType;
	eControls				currentDirection;
	int						hitPoints;
	bool					mortal;
	Model					_model;
	int						stuck;
	//Powerup					*powerup; // think about how bombs are ordered when powerup is active

protected:

private:

};

#endif