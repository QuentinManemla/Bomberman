#include "../includes/Menu.hpp"

/******************************************************************************/
/*	Mandatory class functions 
/******************************************************************************/

MenuState::MenuState( Engine & engine ){
	std::cout << "Menu constructed" << std::endl; // debug
	this->_engine = &engine;
	//this->_mainMenu = new std::vector<std::string> temp{"New game", "Load game", "Options", "Credits", "Quit"};
	std::string arrMainMenu[5] = {"New game", "Load game", "Options", "Credits", "Quit"};
	this->_mainMenu.insert(this->_mainMenu.end(), std::begin(arrMainMenu), std::end(arrMainMenu));
	std::string arrOptionsMenu[5] = {"Controls", "Fullscreen", "Resolution", "Volume", "Back"};
	this->_optionsMenu.insert(this->_optionsMenu.end(), std::begin(arrOptionsMenu), std::end(arrOptionsMenu));
	this->_menuIndex = 0;
	this->_subState = 0;
}

MenuState::MenuState( void ){
	std::cout << "Menu constructed" << std::endl; // debug
}

MenuState::~MenuState( void ){
	std::cout << "Menu destructed" << std::endl; // debug
}

/******************************************************************************/
/*	General state functions 
/******************************************************************************/

void MenuState::update( eControls key ){
	std::cout << "Menu update" << std::endl; // debug
	this->_changeSelection( key );
}

void MenuState::render( void ) {
	this->_engine->clear();
	switch (this->_subState){
		case 0:
			this->_engine->printMenu(this->_mainMenu, this->_menuIndex, "Assets/Images/main_menu_backgrond.png");
			break;
		case 1:
			this->_engine->printMenu(this->_optionsMenu, this->_menuIndex, "Assets/Images/main_menu_backgrond.png");
			break;
	};
	this->_engine->render();
	std::cout << "Menu render" << std::endl; // debug
}

/******************************************************************************/
/*	State-specific functions
/******************************************************************************/

void	MenuState::_changeSelection( eControls key){
	static	int held = 1; // set to 1 initially to avoid accidental selection on state switch

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
			if (!(held)){
				this->_makeSelection();
			}
			held = 1;
			break;
		case IDLEKEY:
			held = 0;
		default:
			break;
	};
	//this->_menuIndex = std::abs(this->_menuIndex % 5); // circular menu selection feature. Requires additional logic. I vote nah
	std::cout << "Menu option: " << this->_mainMenu[this->_menuIndex] << std::endl; // debug
}

void	MenuState::_makeSelection( void ){
	std::cout << "Selected " << this->_mainMenu[this->_menuIndex] << "! (" << this->_menuIndex << ")" << std::endl; // debug
	
	// reset _menuIndex; // (maybe? Only when not switching state I guess?)
	
	// update state depending on selection:
	if (this->_menuIndex == 0){ // test
		this->_engine->state = PLAY; // test
	}
	else if (this->_menuIndex == 2){
		this->_subState = 1;
	}
	else if (this->_menuIndex == 4){ // test
		exit(0); // test
	}
}
