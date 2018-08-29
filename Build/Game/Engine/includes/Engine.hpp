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

		/********************************************************************************************/
		/*	Keyboard Input Functions 																*/
		/*	getkey( void ) gets the "_Active" private memeber of the Engine which containts the 	*/
		/*	current actively pressed key that is set using the key_callback function				*/
		/********************************************************************************************/
		eControls		getkey( void );
		static void 	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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