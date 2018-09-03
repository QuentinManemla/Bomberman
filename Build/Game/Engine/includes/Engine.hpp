#ifndef ENGINE_HPP
# define ENGINE_HPP
# define GLEW_STATIC

# include <GL/glew.h>
# include <GL/glut.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

# include <vector>
# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

# include <ft2build.h>
# include <freetype/freetype.h>
# include <freetype/ftglyph.h>
# include <freetype/ftoutln.h>
# include <freetype/fttrigon.h>
# include FT_FREETYPE_H

# include <map>

# include "../../Sound/includes/Sound.hpp"
# include "../../Game/includes/enumCONTROLS.hpp"
# include "TextRenderer.hpp"
# include "Shader.hpp"

class	Engine {
	public:
		Engine();
		~Engine();

		void			engineInit( void );
		void			render( void );
		void			clear( void );

		void			print2DText(std::string text, int pos_x, int pos_y);
		/********************************************************************************************/
		/*	Keyboard Input Functions 																*/
		/*	getkey( void ) gets the "_Active" private memeber of the Engine which containts the 	*/
		/*	current actively pressed key that is set using the key_callback function				*/
		/********************************************************************************************/
		bool			getkey( int key );

		static void processKeys(unsigned char key, int x, int y);
		/* Exception */
		class GLFWInitializationError: public std::exception {
			virtual const char* what() const throw();
		};

		class GLEWInitializationError: public std::exception {
			virtual const char* what() const throw();
		};

	private:
		GLFWwindow				*_Window;
		Engine					*_MYWindow;
		int						_WindowHeight;
		int						_WindowWidth;
		eControls				_ActiveKey;
		Sound					_SoundEngine;
		Shader					_Shader;
		glfreetype::font_data	_Font;
};

#endif // !ENGINE_HPP