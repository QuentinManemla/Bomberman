# include "../includes/Engine.hpp"
/********************************************************************************/
/*	Required functions															*/
/********************************************************************************/

int		Engine::held = 1;


Engine::Engine(): _WindowWidth(1024),_WindowHeight(768) {
	std::cout << "Engine constructed" << std::endl;
	// initialising controls struct
	this->_sControls.LEFT_KEY = GLFW_KEY_LEFT;//263;
	this->_sControls.UP_KEY = GLFW_KEY_UP;//265;
	this->_sControls.RIGHT_KEY = GLFW_KEY_RIGHT;//262;
	this->_sControls.DOWN_KEY = GLFW_KEY_DOWN;//264;
	this->_sControls.ENTER_KEY = GLFW_KEY_ENTER;//257;
	this->_sControls.ESCAPE_KEY = GLFW_KEY_ESCAPE;//256;
	this->_sControls.FIRE_KEY = GLFW_KEY_Z;//90; defaults to z
	this->_sControls.ACTION_KEY = GLFW_KEY_X;//88; defaults to x

	return ;
}

Engine::~Engine() {
	std::cout << "Engine destructed" << std::endl;
	this->_Font.clean();
}

/********************************************************************************/
/*	Engine specific functions													*/
/********************************************************************************/

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
	if( this->_Window == NULL ){ // Exception
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
	}
	glfwMakeContextCurrent(this->_Window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw (GLEWInitializationError());
	std::cout << "GLEW Initialized Successfully" << std::endl;

	glfwSetInputMode(this->_Window, GLFW_STICKY_KEYS, GL_TRUE);
	this->_Font.init("Assets/Fonts/neon_pixel.ttf", 30 /* size */);

	std::cout << "GL Version: " <<  (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	this->_SoundEngine.init();
	//this->muteSound();
}

void	Engine::clear( void ) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(255.0, 255.0, 255.0, 0.0);
	glPushMatrix();
	glLoadIdentity();
}

void	Engine::render( void ) {
	glPopMatrix();
	glfwSwapBuffers(this->_Window);
	glfwPollEvents();
}

void		Engine::playSound( std::string soundPath, bool loop) {
	if (!this->_Mute)
		this->_SoundEngine.play2DSound(soundPath, loop);
}

void		Engine::stopSound( void ) {
	this->_SoundEngine.stopSound();
}

void		Engine::muteSound( void ) {
	this->_Mute = !_Mute;
}
/********************************************************************************/
/*	Text and Menu Rendering Function														*/
/********************************************************************************/

void		Engine::print2DText(std::string text, float pos_x, float pos_y, GLubyte red, GLubyte green, GLubyte blue) {
	glColor3ub(red,green,blue);
	//std::cout << (this->_WindowWidth / 2) << std::endl; // debug
	glfreetype::print(this->_Font, pos_x, pos_y,text);
}

void		Engine::printMenu(std::vector<std::string> menuItems, float pos_x, float pos_y,
int menuIndex, std::string backgroundPath) {
	float		x = 20;
	float 	y = 20;
	for (int i = menuItems.size() - 1;i >= 0; i--) {
		//std::cout << menuItems[i] << std::endl; // debug
		this->print2DText(menuItems[i], x, y, 0, 0, 0xff);
		y += 50;
	}
}


void		Engine::printMenu(std::vector<std::string> menuItems, int menuIndex, std::string backgroundPath) {
	float		x = 20;
	float 	y = (this->_WindowHeight / 2) - (menuItems.size() * 32);
	for (int i = menuItems.size() - 1;i >= 0; i--) {
		//std::cout << menuItems[i] << std::endl; // debug
		float length = menuItems[i].length();
		if (i == menuIndex)
			this->print2DText(menuItems[i], (this->_WindowWidth / 2) - ((length / 2) * 32), y, 0, 0, 0);
		else
			this->print2DText(menuItems[i], (this->_WindowWidth / 2) - ((length / 2) * 32), y, 0, 0, 0xff);
		y += 50;
	}
}

int			Engine::menuHandler( eControls key, int & menuIndex, int lastIndex ){
	switch (key){
			case UP:
			if (!(this->held))
				menuIndex == 0 ? menuIndex = 0 : menuIndex--;
			this->held = 1;
			break;
		case DOWN:
			if (!(this->held))
				menuIndex == lastIndex ? menuIndex = lastIndex : menuIndex++;
			this->held = 1;
			break;
		case ENTER:
			if (!(this->held))
				return (1);
			this->held = 1;
			break;
		case IDLEKEY:
			this->held = 0;
			break;
		case ESCAPE:
			if (!(this->held))
				this->state = BACK;
			this->held = 1;
			break;
		default:
			break;
	};
	return (0);
}

/********************************************************************************/
/*	Keyboard input functions													*/
/********************************************************************************/

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

/********************************************************************************/
/*	FPS management functions													*/
/********************************************************************************/

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

/********************************************************************************/
/*	Exception handling															*/
/********************************************************************************/

const char* Engine::GLFWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLFW");
}

const char* Engine::GLEWInitializationError::what() const throw() {
	return ("[Error (Code: 00)] Failed to initialize GLEW");
}