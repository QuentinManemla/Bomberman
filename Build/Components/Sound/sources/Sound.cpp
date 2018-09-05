#include "../includes/Sound.hpp"

Sound::Sound( void ) {}

Sound::~Sound( void ) {
	this->_soundEngine->drop();
}

void		Sound::init( void ) {
	this->_soundEngine = irrklang::createIrrKlangDevice();
	if (!this->_soundEngine)
		std::cout << "Could Not Create Sound Engine" << std::endl;
}

void		Sound::stopSound( void ) {
	this->_soundEngine->stopAllSounds();
}

void		Sound::play2DSound( std::string soundPath, bool loop ) {
	this->_soundEngine->play2D(soundPath.c_str(), loop);
}