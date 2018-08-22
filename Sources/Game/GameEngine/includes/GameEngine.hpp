#ifndef GAME_ENGINE_HPP
# define GAME_ENGINE_HPP
# define GLEW_STATIC

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

class	GameEngine {
	public:
		GameEngine(); // Default Constructor
		~GameEngine();
};

#endif // !GAME_ENGINE_HPP