#ifndef QUIT_HPP
# define QUIT_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

//!Quit menu state
class QuitState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	QuitState( Engine & engine );
	~QuitState( void );

private:
	void	_makeSelection( void );

};

#endif