#ifndef SAVEQUIT_HPP
# define SAVEQUIT_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"
# include <dirent.h>

class SaveQuitState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	SaveQuitState( Engine & engine );
	SaveQuitState(SaveQuitState const & src);
	SaveQuitState	&operator=(SaveQuitState const &rhs);
	~SaveQuitState( void );

private:
	void	_makeSelection( void );

};

#endif