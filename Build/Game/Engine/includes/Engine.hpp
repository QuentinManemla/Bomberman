#ifndef ENGINE_HPP
# define ENGINE_HPP
# define GLEW_STATIC

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

# include <vector>
# include <iostream>
# include <string.h>

# include "../../Sound/includes/Sound.hpp"
# include "../../Game/includes/enumCONTROLS.hpp"

class	Engine {
	public:
		Engine();
		~Engine();

		void			engineInit( void );
		void			render( void );

		void			setkey(eControls key);

		/* Exception */
		class GLFWInitializationError: public std::exception {
			virtual const char* what() const throw();
		};

		class GLEWInitializationError: public std::exception {
			virtual const char* what() const throw();
		};

	private:
		GLFWwindow		*_Window;
		int				_WindowHeight;
		int				_WindowWidth;
		eControls		_ActiveKey;
		Sound			_SoundEngine;

};

#endif // !ENGINE_HPP