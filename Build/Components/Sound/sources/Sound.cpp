#include "../includes/Sound.hpp"

Sound::Sound( void ): _volume(1.0f) {}

Sound::~Sound( void ) {
	this->_soundEngine->drop();
}

void		Sound::init( void ) {
	this->_soundEngine = irrklang::createIrrKlangDevice();
	if (!this->_soundEngine)
		std::cout << "Could Not Create Sound Engine" << std::endl;
	
	this->_Intro = this->_soundEngine->addSoundSourceFromFile("Assets/Audio/Intro_State.wav");
	this->_Selection = this->_soundEngine->addSoundSourceFromFile("Assets/Audio/Enter_Key.wav");
	this->_Play = this->_soundEngine->addSoundSourceFromFile("Assets/Audio/Bomberman-Music.wav");
	this->_PlaceBomb = this->_soundEngine->addSoundSourceFromFile("Assets/Audio/punch.wav");
	this->_EnterKey = this->_soundEngine->addSoundSourceFromFile("Assets/Audio/Selection.wav");
	this->_Explode = this->_soundEngine->addSoundSourceFromFile("Assets/Audio/bomb-explode.wav");
}

void		Sound::stopSound( void ) {
	this->_soundEngine->stopAllSounds();
}

void		Sound::play2DSound( std::string soundPath, bool loop ) {
	this->_soundEngine->play2D(soundPath.c_str(), loop);
}

void		Sound::playSoundSource(	irrklang::ISoundSource* sound, bool loop ) {

	sound->setDefaultVolume(this->_volume);
	this->_soundEngine->play2D(sound, loop);
}