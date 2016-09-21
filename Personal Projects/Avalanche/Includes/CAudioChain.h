#ifndef SFMLG_CAUDIOCHAIN_H
#define SFMLG_CAUDIOCHAIN_H
#include "IAudioChainLink.h"
#include "CDelayAudioLink.h"
#include "CSoundAudioLink.h"
#include "CMusicAudioLink.h"
#include <queue>
class CAudioChain
{
	private:
		std::queue<IAudioChainLink*> m_AudioChain;
	public:
		void AddToChain(IAudioChainLink* Link);
		void StartChain();
		bool Update(sf::Time ElapsedTime);
		void Destroy();
};

#endif