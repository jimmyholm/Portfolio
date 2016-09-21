#ifndef SFMLG_IAUDIOCHAINLINK_H
#define SFMLG_IAUDIOCHAINLINK_H
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include <boost\smart_ptr.hpp>
#include "CSAudioManager.h"

enum EAudioChainState
{
	ACS_ACTIVE,
	ACS_DEAD
};
class IAudioChainLink
{
	protected:
		EAudioChainState m_State;
	public:
		virtual void Update(sf::Time ElapsedTime) = 0;
		inline const EAudioChainState getState() {return m_State;}
		virtual void Play() = 0;
		virtual void Stop() = 0;
		virtual void Destroy() = 0;
};

#endif