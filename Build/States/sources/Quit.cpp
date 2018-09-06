#include "../includes/Quit.hpp"

QuitState::QuitState( Engine & engine ){
	this->_type = "Quit";
	std::cout << this->getType() << " constructed" << std::endl;
	this->_engine = &engine;
	this->_menuIndex = 0;

	std::string arrQuitMenu[2] = {"NO", "YES"};
	this->_menu.insert(this->_menu.end(), std::begin(arrQuitMenu), std::end(arrQuitMenu));
}

QuitState::~QuitState( void ){
	std::cout << this->getType() << " destructed" << std::endl;
}

void	QuitState::_makeSelection( void){
	std::cout << "Selected " << this->_menu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	if (this->_menuIndex == 1)
		exit(0);
	else if (this->_menuIndex == 0)
		this->_engine->state = MENU;
}