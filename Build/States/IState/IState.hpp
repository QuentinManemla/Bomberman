#ifndef ISTATE_HPP
# define ISTATE_HPP

# include "../../Game/Engine/includes/Engine.hpp"

class IState {
public:
	virtual void update( Engine &engine ) = 0;
	virtual void render( Engine	&engine ) = 0;
	virtual ~IState( ) {};

protected:

private:

};

#endif