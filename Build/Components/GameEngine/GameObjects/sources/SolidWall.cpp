# include "../includes/SolidWall.hpp"

SolidWall::SolidWall( eGameObjectType type, Vector3d *position ){
	this->strType = "SolidWall";
	this->position = position;
	this->eType = type;
	this->state = ALIVE;
	this->mortal = 0;
}

SolidWall::SolidWall(SolidWall const & src) {}

SolidWall	&SolidWall::operator=(SolidWall const &rhs) {}

SolidWall::~SolidWall( void ){

}