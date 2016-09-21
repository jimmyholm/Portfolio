#include "CMusicAudioLink.h"

CMusicAudioLink::CMusicAudioLink(std::string Music, int MaxRepeats, sf::Int32 LoopTo) : m_Counter(0), m_LoopTo(sf::milliseconds(LoopTo)), m_MaxRepeats(MaxRepeats)
{
	m_Music = CSAudioManager::GetInstance()->GetMusic(Music);
	m_State = ACS_ACTIVE;
}

void CMusicAudioLink::Play()
{
	m_Music->play();
	m_State = ACS_ACTIVE;
}

void CMusicAudioLink::Stop()
{
	m_Music->stop();
	m_State = ACS_DEAD;
}

void CMusicAudioLink::Destroy()
{
	Stop();
	m_Music.reset();
}

void CMusicAudioLink::Update(sf::Time TimeElapsed)
{
	if(m_Music->getStatus() == sf::Music::Stopped)
	{
		if((m_MaxRepeats == -1) || (++m_Counter < m_MaxRepeats))
		{
			Play();
			m_Music->setPlayingOffset(m_LoopTo);
		}
		else
		{
			m_State = ACS_DEAD;
		}
	}
}