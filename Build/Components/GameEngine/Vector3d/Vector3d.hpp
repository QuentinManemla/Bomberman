#ifndef VECTOR3D_HPP
# define VECTOR3D_HPP

//! positions in 3D space
class Vector3d {
public:
	Vector3d( float vX, float vY, float vZ);
	Vector3d( void );
	~Vector3d( void );

	//! increases the vector x
	void	incX( float num);
	//! increases the vector y
	void	incY( float num);
	//! increases the vector z
	void	incZ( float num);
	//! decreases the vector x
	void	decX( float num);
	//! decreases the vector y
	void	decY( float num);
	//! decreases the vector z
	void	decZ( float num);
	//! sets all 3 vectors
	void	setAll( float vX, float vY, float vZ);
	float	vX;
	float	vY;
	float	vZ;

protected:

private:

};

#endif