#ifndef ISTATE_HPP
# define ISTATE_HPP

class IState {
public:
	virtual ~IState( void ) = 0;
	virtual void update( void ) = 0;
	virtual void render( void ) = 0;

protected:

private:

};

#endif