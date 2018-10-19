#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include <string>
# include <vector>

# include "../../enums/enumGameObjectState.hpp"
# include "../../enums/enumGameObjectType.hpp"
# include "../../Vector3d/Vector3d.hpp"
# include "../../../Engine/includes/Engine.hpp"

//! Base game object
class GameObject {
public:
	//! Constructer
	GameObject( eGameObjectType type, Vector3d *position );
	GameObject( void );
	~GameObject( void );

	//addComponent
	//getComponent

	std::string				modelPath; //!< Path the the model
	std::string				spritePath;
	Vector3d				*position; //!< Position in 3D space
	Vector3d				*destination;
	int						step;
	float					velocity; //!< Speed at which it can move
	eGameObjectState		state;
	eGameObjectType			eType; //!< The type of object it is
	std::string				strType;
	eControls				currentDirection; //!< Current direction
	int						hitPoints; //!< Remaining health
	bool					mortal; //!< Bool of deathness
	Model					_model;
	int						stuck;
	//Powerup					*powerup; // think about how bombs are ordered when powerup is active

protected:

private:

};

#endif