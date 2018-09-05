#ifndef OPTIONS_HPP
# define OPTIONS_HPP

# include <iostream>
# include <vector>
# include "IState.hpp"

class OptionsState : public IState {
public:
	// constructor that takes ptr to GameEngine
	OptionsState( void );
	OptionsState( Engine & engine );
	~OptionsState( void );

	std::string					getType( void ); // debug

	void						update( eControls key );
	void						render( void );

protected:

private:
	void						_changeSelection( eControls key );
	void						_makeSelection( void );

	int							_menuIndex;
	int							_menuSize;
	std::vector<std::string>	_optionsMenu;
	Engine						*_engine;
	std::string					_type; // debug
};

#endif