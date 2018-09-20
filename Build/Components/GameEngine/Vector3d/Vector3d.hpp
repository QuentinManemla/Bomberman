#ifndef VECTOR3D_HPP
# define VECTOR3D_HPP

class Vector3d {
public:
	Vector3d( float vX, float vY, float vZ);
	Vector3d( void );
	~Vector3d( void );

	void	incX( float num);
	void	incY( float num);
	void	incZ( float num);
	void	decX( float num);
	void	decY( float num);
	void	decZ( float num);
	void	setAll( float vX, float vY, float vZ);
	float	vX;
	float	vY;
	float	vZ;

protected:

private:

};

#endif