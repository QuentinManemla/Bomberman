# include "../includes/Engine.hpp"

Engine::Engine() {
	std::cout << "Engine constructed" << std::endl;
	// initialising controls struct
	this->_sControls.LEFT_KEY = 263;
	this->_sControls.UP_KEY = 265;
	this->_sControls.RIGHT_KEY = 262;
	this->_sControls.DOWN_KEY = 264;
	this->_sControls.ENTER_KEY = 257;
	this->_sControls.ESCAPE_KEY = 256;
	this->_sControls.FIRE_KEY = 90;
	this->_sControls.ACTION_KEY = 88;
	return ;
}

Engine::~Engine() {
	std::cout << "Engine destructed" << std::endl;
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
	//glfwSetKeyCallback(this->_Window, Engine::key_callback);
}

void	Engine::render( void ) { // investigate optimisation
	glfwSwapBuffers(this->_Window);
	std::cout << "engine render" << std::endl; // debug
	glfwPollEvents();
}

/********************************************************************************************/
/*	Keyboard Input Functions BEGIN															*/
/********************************************************************************************/

eControls	Engine::getInput(){
	// run through array or struct of values. struct most likely
	if (this->_getKey( this->_sControls.LEFT_KEY ))
		return (LEFT);
	if (this->_getKey( this->_sControls.UP_KEY ))
		return (UP);
	if (this->_getKey( this->_sControls.RIGHT_KEY ))
		return (RIGHT);
	if (this->_getKey( this->_sControls.DOWN_KEY ))
		return (DOWN);
	if (this->_getKey( this->_sControls.ENTER_KEY ))
		return (ENTER);
	if (this->_getKey( this->_sControls.ESCAPE_KEY ))
		return (ESCAPE);
	if (this->_getKey( this->_sControls.ACTION_KEY ))
		return (LEFT);
	if (this->_getKey( this->_sControls.FIRE_KEY ))
		return (LEFT);
	return (IDLEKEY);
}

bool		Engine::_getKey( int key ) {
	int state = glfwGetKey(this->_Window, key);
	if (state == GLFW_PRESS)
		return (true);
	return (false);
}

/********************************************************************************************/
/*	FPS management BEGIN																	*/
/********************************************************************************************/

void		Engine::FPSManager( void ){
	static int				index = 0;
	double					deltaTime = 0;
	static double			frames[100]; // set samples
	double					averageTime = 0;
	static int				samplesFull = 0;
	static double			prevTime = 0;
	double					currentTime = 0;

	currentTime = glfwGetTime();
	deltaTime = currentTime - prevTime;
	frames[index++] = deltaTime;

	if (index == 100){
		samplesFull = 1;
		index = 0;
	}

	for (int i = 0; i < 100; i++){
		averageTime += frames[i];
	}

	if (samplesFull)
		averageTime /= 100;
	else
		averageTime /= index;

	std::cout << "Average FPS: " << 1.0f / averageTime << std::endl;
	prevTime = currentTime;

	// delay here
}

/********************************************************************************************/
/*	Exceptions BEGIN																		*/
/********************************************************************************************/


const char* Engine::GLFWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLFW");
}

const char* Engine::GLEWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLEW");
}