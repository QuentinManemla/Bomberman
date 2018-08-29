# include "../includes/Engine.hpp"

Engine::Engine() {return ;}

Engine::~Engine() {return ;}

void  Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Engine	*_engine =  static_cast<Engine *>(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS) {
		switch(key) {
			case ( GLFW_KEY_ESCAPE ):
				_engine->_ActiveKey = ESCAPE;
				break;
			case ( GLFW_KEY_LEFT ):
				_engine->_ActiveKey = LEFT;
				break;
			case ( GLFW_KEY_RIGHT ):
				_engine->_ActiveKey = RIGHT;
				break;
			case ( GLFW_KEY_UP ):
				_engine->_ActiveKey = UP;
				break;
			case ( GLFW_KEY_DOWN ):
				_engine->_ActiveKey = DOWN;
				break;
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
	glfwSetKeyCallback(this->_Window, Engine::key_callback);
}

void	Engine::render( void ) {
	glfwSwapBuffers(this->_Window);
	glfwPollEvents();
}

eControls		Engine::getKey( void ) {
	return (this->_ActiveKey);
}

/* Exceptions */

const char* Engine::GLFWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLFW");
}

const char* Engine::GLEWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLEW");
}