#ifndef SFMLG_CAUDIOLINK_H
#define SFMLG_CAUDIOLINK_H
#include "IAudioChainLink.h"

class CSoundAudioLink : public IAudioChainLink
{
	protected:
		SOUNDPTR m_Sound;
		int		 m_MaxRepeats;
		int		 m_Counter;
	public:
		CSoundAudioLink(std::string SoundName, int MaxRepeats);

		void Update(sf::Time TimeElapsed);
		void Play();
		void Stop();
		void Destroy();

};

#endif