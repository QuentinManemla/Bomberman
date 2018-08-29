#ifndef SHADER_HPP
# define SHADER_HPP

# include <GL/glew.h>
# include <GL/glut.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

# include <vector>
# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

class Shader {
    public:

        Shader();
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        ~Shader();

        void use();
        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;

    private:
        unsigned int ID:
};
#endif // !SHADER_HPP