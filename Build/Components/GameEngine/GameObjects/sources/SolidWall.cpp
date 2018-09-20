# include "../includes/SolidWall.hpp"

SolidWall::SolidWall( eGameObjectType type, Vector3d *position ){
	this->strType = "SolidWall";
	this->position = position;
	this->eType = type;
}

SolidWall::~SolidWall( void ){

}