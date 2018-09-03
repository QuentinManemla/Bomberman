# include "../includes/Engine.hpp"

Engine::Engine(): _WindowWidth(1024),_WindowHeight(768) {}

Engine::~Engine() {}

unsigned int VBO, VAO;

void	Engine::engineInit( void ) {
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit())
		throw (GLFWInitializationError());
	std::cout << "GLFW Initialized Successfully" << std::endl;
	this->_Window = glfwCreateWindow(this->_WindowWidth, this->_WindowHeight, "Bomberman", NULL, NULL);
	if( this->_Window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
	}
	glfwMakeContextCurrent(this->_Window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw (GLEWInitializationError());
	std::cout << "GLEW Initialized Successfully" << std::endl;

	// 	// get version info
	// const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	// const GLubyte* version = glGetString(GL_VERSION); // version as a string
	// printf("Renderer: %s\n", renderer);
	// printf("OpenGL version supported %s\n", version);

	glfwSetInputMode(this->_Window, GLFW_STICKY_KEYS, GL_TRUE);
	this->_Font.init("Assets/Fonts/Bomberman.ttf", 30 /* size */);

	std::cout << "GL Version: " <<  (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void	Engine::print2DText(std::string text, int pos_x, int pos_y) {
	glColor3ub(0,0,0xff);
	std::cout << (this->_WindowWidth / 2) << std::endl;
	glfreetype::print(this->_Font, 512 / 2, (this->_WindowHeight / 2),text);
}

void	Engine::render( void ) {	
	glPopMatrix();
	glfwSwapBuffers(this->_Window);
	glfwPollEvents();
}

void	Engine::clear( void ) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
}


/********************************************************************************************/
/*	Keyboard Input Functions BEGIN															*/
/********************************************************************************************/

bool		Engine::getkey( int key ) {
	int state = glfwGetKey(this->_Window, key);
	if (state == GLFW_PRESS)
		return (true);
	return (false);
}

/********************************************************************************************/
/*	Keyboard Input Functions END															*/
/********************************************************************************************/


/* Exceptions */

const char* Engine::GLFWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLFW");
}

const char* Engine::GLEWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLEW");
}