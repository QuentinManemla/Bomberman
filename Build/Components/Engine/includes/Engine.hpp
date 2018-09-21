#ifndef ENGINE_HPP
# define ENGINE_HPP
# define GLEW_STATIC

# include <glad/glad.h>
//# include <GL/glew.h>
# include <GL/glut.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

# include <GLFW/glfw3.h>
# include <glm/glm.hpp>
# include <stb_image.h>
# include <vector>
# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

# include <assimp/Importer.hpp>
# include <assimp/scene.h>
# include <assimp/postprocess.h>

# include <ft2build.h>
# include <freetype/freetype.h>
# include <freetype/ftglyph.h>
# include <freetype/ftoutln.h>
# include <freetype/fttrigon.h>
# include FT_FREETYPE_H

# include <map>

# include "../../Sound/includes/Sound.hpp"
# include "../../Game/includes/enumControls.hpp"
# include "Text.hpp"
# include "Camera.hpp"
# include "Model.hpp"
# include <string.h>
# include <vector>
# include "../../Sound/includes/Sound.hpp"
# include "../../Game/includes/enumControls.hpp"
# include "structControls.hpp"
# include "../../../States/includes/enumState.hpp"

class	Engine {
	public:
		Engine();
		~Engine();

		void			engineInit( void );
		void			render( void );
		void			clear( void );

		void			triangle( void );
		void			draw( void );
		void 			drawModel( float transX, float transY, float transZ );
		void 			drawModel2( float transX, float transY, float transZ );
		GLuint			createShader(const char* vertexPath, const char* fragmentPath);
		void 			checkCompileErrors(unsigned int shader, std::string type);

		void			playSound( std::string soundPath, bool loop);
		void			stopSound( void );
		void			muteSound( void );
		/********************************************************************************************/
		/*	Text Rendering Functions 																*/
		/*	print2DText() Takes in the text and X & Y position to print out on the Window			*/
		/*	current actively pressed key that is set using the key_callback function				*/
		/********************************************************************************************/

		void			print2DText(std::string text, float pos_x, float pos_y, float red, float green, float blue);
		void			printMenu(std::vector<std::string> menuItems, float pos_x, float pos_y, int menuIndex, std::string backgroundPath);		
		void			printMenu(std::vector<std::string> menuItems, int menuIndex, std::string backgroundPath);
		int				menuHandler( eControls key, int & menuIndex, int lastIndex );

		/********************************************************************************************/
		/*	Keyboard Input Functions 																*/
		/*	getkey( void ) gets the "_Active" private memeber of the Engine which containts the 	*/
		/*	current actively pressed key that is set using the key_callback function				*/
		/********************************************************************************************/

		eControls		getInput( void );
		static void		processKeys(unsigned char key, int x, int y);

		/********************************************************************************************/
		/*	Display Monitor Functions 																*/
		/* */
		/********************************************************************************************/

		void			setFullScreen( void );
		void			setWindowed( void );
		void			setResolution( int width, int height);


		/* Timer functions */
		void			FPSManager();

		/* Exception */
		class GLFWInitializationError: public std::exception {
			virtual const char* what() const throw();
		};

		class GLEWInitializationError: public std::exception {
			virtual const char* what() const throw();
		};

		eState					state;
		int						_WindowHeight;
		int						_WindowWidth;
		static int				held; // test
		Camera 					_Camera;

	private:
		GLFWwindow				*_Window;
		const GLFWvidmode		*_Mode;
		GLFWmonitor				*_Monitor;
		eControls				_ActiveKey;
		Sound					_SoundEngine;
		Text					_TextEngine;
		sControls				_sControls;
		bool					_getKey( int key );
		bool					_Mute;
		Shader					_Shader;
		Shader					_ModelShader;
		Model					_TestModel;
		Model					_TestModel2;
		Shader					_ShaderText;
};

#endif // !ENGINE_HPP