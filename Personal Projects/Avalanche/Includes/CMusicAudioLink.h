#ifndef SFMLG_CMUSICAUDIOLINK_H
#define SFMLG_CMUSICAUDIOLINK_H
#include "IAudioChainLink.h"

class CMusicAudioLink : public IAudioChainLink
{
	protected:
		MUSICPTR m_Music;
		int m_MaxRepeats;
		int m_Counter;
		sf::Time m_LoopTo;
	public:
		CMusicAudioLink(std::string Music, int MaxRepeats, sf::Int32 LoopTo);
		void Play();
		void Update(sf::Time TimeElapsed);
		void Stop();
		void Destroy();
};

#endif