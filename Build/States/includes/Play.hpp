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

	float			_positionTime;
	float			_positionPitch;
};

#endif