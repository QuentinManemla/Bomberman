# include "../includes/Engine.hpp"

Engine::Engine() {return ;}

Engine::~Engine() {return ;}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case ( GLFW_KEY_ESCAPE ):
				std::cout << "ESCAPE" << std::endl;
				this->_ActiveKey = ESCAPE;
			// case ( GLFW_KEY_LEFT ):
			// 	return (LEFT);
			// case ( GLFW_KEY_RIGHT ):
			// 	return (RIGHT);
			// case ( GLFW_KEY_UP ):
			// 	return (UP);
			// case ( GLFW_KEY_DOWN ):
			// 	return (DOWN);
			default:
				break;
		}
	}
}

void	Engine::engineInit( void ) {
	// GLFW Hint Setup
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit())
		throw (GLFWInitializationError());
	std::cout << "GLFW Initialized Successfully" << std::endl;
	this->_Window = glfwCreateWindow(1024, 768, "Bomberman", NULL, NULL);
	if( this->_Window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
	}
	glfwMakeContextCurrent(this->_Window);
	if (glewInit() != GLEW_OK)
		throw (GLEWInitializationError());
	std::cout << "GLEW Initialized Successfully" << std::endl;
	glfwSetInputMode(this->_Window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(this->_Window, key_callback);
}

void	Engine::render( void ) {
	glfwSwapBuffers(this->_Window);
	glfwPollEvents();
	if (this->_ActiveKey == ESCAPE) {
		glfwTerminate();
	}
}

void	Engine::setkey(eControls key) {
	this->_ActiveKey = key;
}

/* Exceptions */

const char* Engine::GLFWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLFW");
}

const char* Engine::GLEWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLEW");
}