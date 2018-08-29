#ifndef ISTATE_HPP
# define ISTATE_HPP

# include "../../Components/Engine/includes/Engine.hpp"

class IState {
public:
	virtual void update( void ) = 0;
	virtual void render( Engine	& engine ) = 0;
	virtual ~IState( ) {};

protected:

private:

};

#endif