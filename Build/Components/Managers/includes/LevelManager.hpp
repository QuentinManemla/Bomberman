#ifndef LEVELMANAGER_HPP
# define LEVELMANAGER_HPP

# include <iostream>
# include <string>
# include <vector>

class LevelManager {
public:
	LevelManager( void );
	~LevelManager( void );

	void	generateMap( void );
	void	validMap(); // checks if map is valid (no dead ends)

	// sets initial spawn positions of enemies and powerups on map (floppy)
	void	placeEnemies( void ); // might use array here
	void	placePowerups( void ); // might use array as well
	void	placeDoor( void ); 

	int		mapMax;
	int		level;

protected:

private:

};

#endif