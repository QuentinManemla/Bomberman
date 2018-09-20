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

protected:

private:
	ObjectManager	*_OM;
	Engine			*_engine;
	std::string		_type; // debug
	bool			_firstInit;
	float			_positionTime;
	float			_positionPitch;
	float			y;
	float			x;
	float 			z;

};

#endif