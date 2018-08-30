#ifndef ENGINE_HPP
# define ENGINE_HPP
# define GLEW_STATIC

# include <GL/glew.h>
# include <GL/glut.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

# include <vector>
# include <iostream>
# include <string.h>

# include "../../Sound/includes/Sound.hpp"
# include "../../Game/includes/enumCONTROLS.hpp"
# include "structControls.hpp"
# include "../../../States/enumState.hpp"

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

		eControls		getInput( void );

		static void processKeys(unsigned char key, int x, int y);
		/* Exception */
		class GLFWInitializationError: public std::exception {
			virtual const char* what() const throw();
		};

		class GLEWInitializationError: public std::exception {
			virtual const char* what() const throw();
		};

		eState			state;

	private:
		GLFWwindow		*_Window;
		Engine			*_MYWindow;
		int				_WindowHeight;
		int				_WindowWidth;
		eControls		_ActiveKey;
		Sound			_SoundEngine;
		sControls		_sControls;
		bool			_getKey( int key );

};

#endif // !ENGINE_HPP