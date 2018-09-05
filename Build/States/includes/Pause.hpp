#ifndef PAUSE_HPP
# define PAUSE_HPP

# include <iostream>
# include <vector>
# include "IState.hpp"

class PauseState : public IState {
public:
	// constructor that takes ptr to GameEngine
	PauseState( void );
	PauseState( Engine & engine );
	~PauseState( void );

	std::string					getType( void ); // debug

	void						update( eControls key );
	void						render( void );

protected:

private:
	void						_changeSelection( eControls key );
	void						_makeSelection( void );

	int							_menuIndex;
	int							_menuSize;
	std::vector<std::string>	_pauseMenu;
	Engine						*_engine;
	std::string					_type; // debug
};

#endif