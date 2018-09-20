#ifndef TEXT_HPP
# include <glad/glad.h>
//# include <GL/glew.h>
# include <GL/glut.h>
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

# include "Shader.hpp"


/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Text {
	public:
		Text( void );
		Text( const char *FontPath, int FontSize );
		~Text( void );

		void	init( const char *FontPath, int FontSize, int Width, int Height );
		void	RenderText( std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color );
	private:
		FT_Library					_ft;
		FT_Face 					_face;
		std::map<GLchar, Character> _Characters;
		Shader 						_shader;
		GLuint 						VAO;
		GLuint						VBO;
};
#endif // !TEXT_HPP