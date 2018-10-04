#ifndef PLAY_HPP
# define PLAY_HPP

# include <iostream>
# include <ctime>
# include <vector>
# include <numeric>
# include <chrono>
# include "IState.hpp"
# include "../../Components/GameEngine/ObjectManager/ObjectManager.hpp"
# include "../../Components/GameEngine/GUIManager/GUIManager.hpp"

class PlayState : public IState {
public:
	// constructor that takes ptr to GameEngine
	PlayState( void );
	PlayState( Engine & engine );
	PlayState( Engine & engine, std::string savePath, bool restart );
	PlayState( Engine & engine, bool cont );
	~PlayState( void );

	std::string		getType( void ); // debug

	void			update( eControls key );
	void			render( void );

	void			drawMap( void );

protected:

private:
	ObjectManager	*_OM;
	GUIManager		*_GM;
	Engine			*_engine;
	std::string		_type; // debug

	//std::chrono::steady_clock::time_point startTime;
	//int				_elapsedSec;
	//int 			_remainingTime;

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