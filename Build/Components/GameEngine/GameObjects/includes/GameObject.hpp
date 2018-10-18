#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include <string>
# include <vector>

# include "../../enums/enumGameObjectState.hpp"
# include "../../enums/enumGameObjectType.hpp"
# include "../../Vector3d/Vector3d.hpp"
# include "../../../Engine/includes/Engine.hpp"

//! base game object
class GameObject {
public:
	//! constructer
	GameObject( eGameObjectType type, Vector3d *position );
	GameObject( void );
	~GameObject( void );

	//addComponent
	//getComponent

	std::string				modelPath; //!< path the the model
	std::string				spritePath;
	Vector3d				*position; //!< position in 3D space
	Vector3d				*destination;
	int						step;
	float					velocity; //!< speed at which it can move
	eGameObjectState		state;
	eGameObjectType			eType; //!< the type of object it is
	std::string				strType;
	eControls				currentDirection; //!< current direction
	int						hitPoints; //!< remaining health
	bool					mortal; //!< bool of deathness
	Model					_model;
	int						stuck;
	//Powerup					*powerup; // think about how bombs are ordered when powerup is active

protected:

private:

};

#endif