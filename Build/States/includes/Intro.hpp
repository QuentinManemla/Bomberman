#ifndef INTRO_HPP
# define INTRO_HPP

# include <iostream>
# include "IState.hpp"

class IntroState : public IState {
public:
	// constructor that takes ptr to GameEngine
	IntroState( void );
	IntroState( Engine & engine );
	IntroState(IntroState const & src);
	IntroState	&operator=(IntroState const &rhs);
	~IntroState( void );

	std::string		getType( void ); // debug

	void 			update( eControls key );
	void 			render( void );

protected:

private:
	Engine			*_engine;
	std::string		_type; // debug
	
};

#endif