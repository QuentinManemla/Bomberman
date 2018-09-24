#ifndef PLAY_HPP
# define PLAY_HPP

# include <iostream>
# include "IState.hpp"
# include "../../Components/GameEngine/ObjectManager/ObjectManager.hpp"

class PlayState : public IState {
public:
	// constructor that takes ptr to GameEngine
	PlayState( void );
	PlayState( Engine & engine );
	~PlayState( void );

	std::string		getType( void ); // debug

	void			update( eControls key );
	void			render( void );

	void			drawMap( void );

protected:

private:
	ObjectManager	*_OM;
	Engine			*_engine;
	std::string		_type; // debug
	float			_positionTime;
	float			_positionPitch;
	float 			start_x;
	float 			start_y;
	float 			start_z;
	float			y;
	float			x;
	float			z;
};

#endif