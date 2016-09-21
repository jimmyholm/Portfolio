#include "CAudioChain.h"

void CAudioChain::AddToChain(IAudioChainLink* Link)
{
	m_AudioChain.push(Link);
}

bool CAudioChain::Update(sf::Time TimeElapsed)
{
	if(m_AudioChain.empty())
		return false;
	if(m_AudioChain.front()->getState() == ACS_DEAD)
	{
		m_AudioChain.front()->Destroy();
		m_AudioChain.pop();
		if(m_AudioChain.empty())
			return false;
		else
			m_AudioChain.front()->Play();
	}
	m_AudioChain.front()->Update(TimeElapsed);
	return true;
}

void CAudioChain::StartChain()
{
	m_AudioChain.front()->Play();
}

void CAudioChain::Destroy()
{
	if(m_AudioChain.empty())
		return;
	m_AudioChain.front()->Stop();
	while(!m_AudioChain.empty())
	{
		m_AudioChain.front()->Destroy();
		delete m_AudioChain.front();
		m_AudioChain.pop();
	}
}