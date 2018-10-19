#ifndef SOUND_HPP
#define SOUND_HPP

# include <irrKlang.h>
# include <iostream>
# include <atomic>
# include <thread>
# include <chrono>
# include <pthread.h>

//! Class that handels the loading and playing of sounds
class Sound {
	public:
		Sound( void );
		~Sound( void );
		//! Initiate the paths for each of the sounds/music used in different occasions
		void		init( void );
		//! Takes in a string indicating the sound/music needed, and a boolean on whether to loop the sound/music or not
		void		play2DSound( std::string soundPath, bool loop );
		//! Takes in a ISoundSource file indicating the sound/music needed, and a boolean on whether to loop the sound/music or not
		void		playSoundSource(	irrklang::ISoundSource* sound, bool loop );
		void		stopSound( void );

		/** Sound Sources **/
		irrklang::ISoundSource*		_Intro;
		irrklang::ISoundSource*		_Selection;
		irrklang::ISoundSource*		_EnterKey;
		irrklang::ISoundSource*		_Play;
		irrklang::ISoundSource*		_Play2;
		irrklang::ISoundSource*		_Play3;
		irrklang::ISoundSource*		_PlaceBomb;
		irrklang::ISoundSource*		_Explode;
		irrklang::ISoundSource*		_Credits;
		irrklang::ISoundSource*		_Menu;
		float						_volume;

	private:
		irrklang::ISoundEngine		*_soundEngine;
};
#endif //!SOUND_HPP