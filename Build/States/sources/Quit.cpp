#include "../includes/Quit.hpp"

QuitState::QuitState( Engine & engine ){
	std::cout << "Quit constructed" << std::endl;
	this->_type = "Quit";
	this->_engine = &engine;
	std::string arrQuitMenu[4] = {"NO", "YES"};
	this->_quitMenu.insert(this->_quitMenu.end(), std::begin(arrQuitMenu), std::end(arrQuitMenu));
	this->_engine = &engine;
	this->_menuIndex = 0;
}

QuitState::QuitState( void ){
	std::cout << "Quit constructed" << std::endl;
}

QuitState::~QuitState( void ){
	std::cout << "Quit destructed" << std::endl;
}

void QuitState::update( eControls key ){
	std::cout << "Quit update" << std::endl;
	if (this->_engine->menuHandler( key, this->_menuIndex, this->_quitMenu.size() - 1 )){
		this->_makeSelection();
	}
}

void	QuitState::_makeSelection( void){
	std::cout << "Selected " << this->_quitMenu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	if (this->_menuIndex == 1)
		exit(0);
	else if (this->_menuIndex == 0)
		this->_engine->state = MENU;
}


void QuitState::render( void ){
	this->_engine->clear();
	this->_engine->printMenu(this->_quitMenu, this->_menuIndex, "Assets/Images/main_menu_backgrond.png");
	this->_engine->render();
	std::cout << "Quit render" << std::endl;
}

std::string QuitState::getType( void ){ //debug
	return this->_type;
}
