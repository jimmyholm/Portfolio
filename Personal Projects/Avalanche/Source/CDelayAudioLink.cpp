#include "CDelayAudioLink.h"

CDelayAudioLink::CDelayAudioLink(sf::Int32 Delay) : m_Delay(Delay), m_Counter(sf::Time::Zero)
{
	m_State = ACS_ACTIVE;
}

void CDelayAudioLink::Update(sf::Time TimeElapsed)
{
	m_Counter += TimeElapsed;
	if(m_Counter.asMilliseconds() >= m_Delay)
		m_State = ACS_DEAD;
}