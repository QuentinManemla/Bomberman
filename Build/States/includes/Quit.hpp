#ifndef QUIT_HPP
# define QUIT_HPP

# include <iostream>
# include "IState.hpp"

class QuitState : public IState {
public:
	// constructor that takes ptr to GameEngine
	QuitState( void );
	QuitState( Engine & engine );
	~QuitState( void );

	std::string		getType( void ); // debug

	void			update( eControls key );
	void			render( void );

protected:

private:
	Engine			*_engine;
	std::string		_type; // debug

};

#endif