#ifndef QUIT_HPP
# define QUIT_HPP

# include <iostream>
# include <vector>
# include "MenuParentState.hpp"

class QuitState : public MenuParentState {
public:
	// constructor that takes ptr to GameEngine
	QuitState( Engine & engine );
	QuitState(QuitState const & src);
	QuitState	&operator=(QuitState const &rhs);
	~QuitState( void );

private:
	void	_makeSelection( void );

};

#endif