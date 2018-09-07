# include "../includes/Engine.hpp"
/********************************************************************************/
/*	Required functions															*/
/********************************************************************************/
unsigned int VBO, VAO;

Engine::Engine(): _WindowWidth(1024),_WindowHeight(768) {
	std::cout << "Engine constructed" << std::endl;
	//GLFW
	if (!glfwInit())
		throw (GLFWInitializationError());

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	std::cout << "GLFW Initialized Successfully" << std::endl;
	this->_Window = glfwCreateWindow(this->_WindowWidth, this->_WindowHeight, "Bomberman", NULL, NULL);
	if( this->_Window == NULL ){ // Exception
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
	}
	glfwMakeContextCurrent(this->_Window);

	glewExperimental = GL_TRUE;
	glewInit();

	glfwSetInputMode(this->_Window, GLFW_STICKY_KEYS, GL_TRUE);
	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->_TextEngine.init("Assets/Fonts/neon_pixel.ttf", 30, this->_WindowWidth, this->_WindowHeight);

	std::cout << "GL Version: " <<  (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	this->_SoundEngine.init();
	this->muteSound();

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
	//this->_Font.clean();
	glfwTerminate();
}

void	Engine::triangle( void ) {
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void	Engine::draw( void ) {
	this->_Shader.use();
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
/********************************************************************************/
/*	Engine specific functions													*/
/********************************************************************************/

void	Engine::engineInit( void ) {
	this->_Shader.init("Assets/Shaders/Default/shader.vs", "Assets/Shaders/Default/shader.fs");
}

void	Engine::clear( void ) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(255.0, 255.0, 255.0, 0.0);
	glPushMatrix();
	glLoadIdentity();
}

void	Engine::render( void ) {	
	//glPopMatrix();
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
	this->_TextEngine.RenderText(text, pos_x, pos_y, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
}

void		Engine::printMenu(std::vector<std::string> menuItems, float pos_x, float pos_y,
int menuIndex, std::string backgroundPath) {
	float		x = 20;
	float 	y = 20;
	for (int i = menuItems.size() - 1;i >= 0; i--) {
		this->print2DText(menuItems[i], x, y, 0, 0, 0xff);
		y += 50;
	}
}


void		Engine::printMenu(std::vector<std::string> menuItems, int menuIndex, std::string backgroundPath) {
	float		x = 20;
	float		y = (this->_WindowHeight / 2) - (menuItems.size() * 32);
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

int			Engine::menuHandler( eControls key, int & menuIndex, int lastIndex, int & held ){
	switch (key){
			case UP:
			if (!(held)) {
				menuIndex == 0 ? menuIndex = 0 : menuIndex--;
				this->playSound("Assets/Audio/Selection.wav", false);
			}
			held = 1;
			break;
		case DOWN:
			if (!(held)) {
				menuIndex == lastIndex ? menuIndex = lastIndex : menuIndex++;
				this->playSound("Assets/Audio/Selection.wav", false);
			}
			held = 1;
			break;
		case ENTER:
			if (!(held))
				return (1);
			held = 1;
			break;
		case IDLEKEY:
			held = 0;
			break;
		case ESCAPE:
			if (!(held))
				this->state = BACK;
			held = 1;
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

GLuint	Engine::createShader(const char* vertexPath, const char* fragmentPath) {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		// open files
		vShaderFile.open("Assets/Shaders/Default/shader.vs");
		fShaderFile.open("Assets/Shaders/Default/shader.fs");
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	this->checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	this->checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	int ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertex);
	glAttachShader(ProgramID, fragment);
	glLinkProgram(ProgramID);
	this->checkCompileErrors(ProgramID, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return (ProgramID);
}

void Engine::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
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