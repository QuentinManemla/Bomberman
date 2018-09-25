# ifndef GUIMANAGER_HPP
# define GUIMANAGER_HPP

# include "../../Engine/includes/Engine.hpp"
# include "../GameObjects/includes/GameObject.hpp"
# include <ctime>

class GUIManager {
	public:
		GUIManager( Engine & engine);
		GUIManager( void );
		~GUIManager( void );
	
	void			update( GameObject *player, int	elapsedSec);
	void			render( void );

	Engine			*engine;
	std::string		_lives;
	std::string		_level;
	std::string		_timeElapsed;
};

#endif // !GUIMANAGER_HPP