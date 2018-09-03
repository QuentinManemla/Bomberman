#ifndef SHADER_HPP

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

class Shader
{
public:
	GLuint ID;

	Shader();
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader	&operator=(Shader const & _rhs);
	~Shader();

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif // !SHADER_HPP