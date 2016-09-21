#ifndef SFMLG_CDELAYAUDIOLINK_H
#define SFMLG_CDELAYAUDIOLINK_H
#include "IAudioChainLink.h"
// A class designed purely to add a timed delay in between two links in the audio chain.
class CDelayAudioLink : public IAudioChainLink
{
	protected:
		sf::Int32 m_Delay;
		sf::Time  m_Counter;
	public:
		CDelayAudioLink(sf::Int32 Delay);
		void Update(sf::Time TimeElapsed);
		void Play()		{}
		void Stop()		{}
		void Destroy()	{}
};
#endif