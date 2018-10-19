# ifndef GUIMANAGER_HPP
# define GUIMANAGER_HPP

# include "../../Engine/includes/Engine.hpp"
# include "../GameObjects/includes/GameObject.hpp"
# include <ctime>

//! Controller for the GUI
class GUIManager {
public:
	GUIManager( Engine & engine);
	GUIManager( void );
	~GUIManager( void );

	//! Update the info in the GUI
	void			update( GameObject *player, int	elapsedSec, int playerScore, int level);
	//! Render the latest changes
	void			render( void );

	Engine			*engine;
	std::string		_lives;
	std::string		_level;
	std::string		_timeElapsed;
	std::string		_points;
};

#endif // !GUIMANAGER_HPP