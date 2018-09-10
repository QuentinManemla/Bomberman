#include "../includes/Factory.hpp"

Factory.Gimme( void ){
}

Factory.~Gimme( void ){
}

Entity* Factory.a( eEntityType entityType ){
	switch (entityType){
		case PLAYER:
			//code here
		case ENEMY1:
			//code here
		case ENEMY2:
			//code here
		case ENEMY3:
			//code here
	};
	// note: enemies may work with enemy style powerups that change a base enemy class
}

Entity* Factory.a( ePowerType powerType ){
}