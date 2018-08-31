#include "../includes/Menu.hpp"

MenuState::MenuState( Engine & engine ){
	std::cout << "Menu constructed" << std::endl; // debug
	this->_engine = &engine;
	this->_MainMenuOptions[0] = "New game";
	this->_MainMenuOptions[1] = "Load game";
	this->_MainMenuOptions[2] = "Options";
	this->_MainMenuOptions[3] = "Credits";
	this->_MainMenuOptions[4] = "Quit";
	this->_menuSize = this->_MainMenuOptions.size();
	this->_menuIndex = 0;
}

MenuState::MenuState( void ){
	std::cout << "Menu constructed" << std::endl; // debug
}

MenuState::~MenuState( void ){
	std::cout << "Menu destructed" << std::endl; // debug
}

void MenuState::update( eControls key ){
	std::cout << "Menu update" << std::endl; // debug
	this->_changeSelection( key );
}

void MenuState::render( void ){
	this->_engine->render();
	// this->_engine->renderMenu( array of options, current index, background/layout );
	std::cout << "Menu render" << std::endl; // debug
}

void	MenuState::_changeSelection( eControls key){
	static	int held = 0;

	switch (key){
		case UP:
			if (!(held))
				this->_menuIndex == 0 ? this->_menuIndex = 0 : this->_menuIndex--;
			held = 1;
			break;
		case DOWN:
			if (!(held))
				this->_menuIndex == 4 ? this->_menuIndex = 4 : this->_menuIndex++;
			held = 1;
			break;
		case ENTER:
			if (!(held))
				this->_makeSelection(this->_menuIndex);
			held = 1;
			break;
		case IDLEKEY:
			held = 0;
		default:
			break;
	};
	//this->_menuIndex = std::abs(this->_menuIndex % 5); // circular menu selection
	std::cout << "Menu option: " << this->_MainMenuOptions[this->_menuIndex] << std::endl; // debug
}

void	MenuState::_makeSelection( int _menuIndex ){
	std::cout << "Selected " << this->_MainMenuOptions[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl;
	
	// reset _menuIndex; (only when not switching state)
	// update state depending on selection
	if (this->_menuIndex == 0) // test
		this->_engine->state = PLAY; // test
	if (this->_menuIndex == 4) // test
		exit(0); // test
}
