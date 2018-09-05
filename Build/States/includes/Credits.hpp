#ifndef CREDITS_HPP
# define CREDITS_HPP

# include <iostream>
# include "IState.hpp"

class CreditsState : public IState {
public:
	// constructor that takes ptr to GameEngine
	CreditsState( void );
	CreditsState( Engine & engine );
	~CreditsState( void );

	std::string		getType( void ); // debug

	void			update( eControls key );
	void			render( void );

protected:

private:
	Engine			*_engine;
	std::string		_type; // debug
	
};

#endif