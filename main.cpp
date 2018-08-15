#include "./headers/Game.hpp"

#include <iostream>

int main(){
	Game game;

	game.gameloop();
	
	return (0);
}
/*
GL =	-rpath $(HOME)/.brew/lib -L$(HOME)/.brew/lib 
GL +=	-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

CFLAGS = -Wall -Werror -Wextra

SFML_FLAGS = -Iincludes/ -I$(HOME)/.brew/Cellar/sfml/2.4.2_1/include/
*/