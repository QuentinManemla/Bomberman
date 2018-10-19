#ifndef VECTOR3D_HPP
# define VECTOR3D_HPP

//! Positions in 3D space
class Vector3d {
public:
	Vector3d( float vX, float vY, float vZ);
	Vector3d( void );
	~Vector3d( void );

	//! Increases the vector x
	void	incX( float num);
	//! Increases the vector y
	void	incY( float num);
	//! Increases the vector z
	void	incZ( float num);
	//! Decreases the vector x
	void	decX( float num);
	//! Decreases the vector y
	void	decY( float num);
	//! Decreases the vector z
	void	decZ( float num);
	//! Sets all 3 vectors
	void	setAll( float vX, float vY, float vZ);
	float	vX;
	float	vY;
	float	vZ;

protected:

private:

};

#endif