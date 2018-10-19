#ifndef MENUPARENT_HPP
# define MENUPARENT_HPP

# include <iostream>
# include <vector>
# include "IState.hpp"

//! Menu state the all menues inherate from
class MenuParentState : public IState {
public:
	MenuParentState( Engine & engine );
	MenuParentState( void );
	~MenuParentState( void );

	std::string					getType( void );
	void						update( eControls key );
	void						render( void );

protected:
	void						_changeSelection( eControls key );
	virtual void				_makeSelection( void ) = 0;

	int							_menuIndex;
	Engine						*_engine;
	std::string					_type;
	std::vector<std::string>	_menu;

};

#endif