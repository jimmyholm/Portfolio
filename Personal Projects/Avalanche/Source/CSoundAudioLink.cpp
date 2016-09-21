#include "CSoundAudioLink.h"

CSoundAudioLink::CSoundAudioLink(std::string SoundName, int MaxRepeats) : m_Counter(0)
{
	if(MaxRepeats < 0)
		throw(std::exception("Error: MaxRepeats must be >= 0 for sound audio link."));

	m_Sound = CSAudioManager::GetInstance()->GetSound(SoundName);
	m_MaxRepeats = MaxRepeats;
	m_State = ACS_ACTIVE;
}

void CSoundAudioLink::Update(sf::Time TimeElapsed)
{
	if(m_Sound->getStatus() == sf::Sound::Stopped)
	{
		if(++m_Counter >= m_MaxRepeats)
			m_State = ACS_DEAD;
		else
		{
			Play();
		}
	}
}

void CSoundAudioLink::Play()
{
	m_Sound->play();
	m_State = ACS_ACTIVE;
}

void CSoundAudioLink::Stop()
{
	m_Sound->stop();
	m_State = ACS_DEAD;
}

void CSoundAudioLink::Destroy()
{
	m_Sound->stop();
	m_Sound.reset();
}