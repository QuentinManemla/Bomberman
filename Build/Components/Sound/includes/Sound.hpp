#ifndef SOUND_HPP
#define SOUND_HPP

# include <irrKlang.h>
# include <iostream>
# include <atomic>
# include <thread>
# include <chrono>
# include <pthread.h>

#pragma comment(lib, "irrKlang.lib")


class Sound {
	public:
		Sound( void );
		~Sound( void );

		void		init( void );
		void		play2DSound( std::string soundPath, bool loop );
		void		playSoundSource(	irrklang::ISoundSource* sound , float volume);
		void		stopSound( void );
	private:
		irrklang::ISoundEngine  *_soundEngine;
};
#endif //!SOUND_HPP