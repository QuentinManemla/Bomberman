#ifndef ISTATE_HPP
# define ISTATE_HPP

# include "../../Components/Engine/includes/Engine.hpp"

class IState {
public:
	virtual void update( eControls key ) = 0;
	virtual void render( void ) = 0;
	virtual std::string getType( void ) = 0; // debug
	virtual ~IState( ) {};

protected:

private:

};

#endif