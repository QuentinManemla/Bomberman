#ifndef INTRO_HPP
# define INTRO_HPP

# include <iostream>
# include "../../IState/IState.hpp"

class IntroState : public IState {
public:
	// constructor that takes ptr to GameEngine
	IntroState( void );
	~IntroState( void );

	void update( Engine &engine );
	void render( Engine	&engine );
protected:

private:
	unsigned int _Textiteration;
};

#endif