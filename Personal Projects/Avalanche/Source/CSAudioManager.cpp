#include "CSAudioManager.h"

CSAudioManager* CSAudioManager::m_Instance = NULL;
CSAudioManager::CSAudioManager()
{
}

CSAudioManager* CSAudioManager::GetInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new CSAudioManager();
	}
	return m_Instance;
}

bool CSAudioManager::LoadSound(std::string FileName, std::string SoundName)
{
	if(m_SoundMap.find(SoundName) != m_SoundMap.end())
	{
		std::string e = boost::str( boost::format("Sound: \"%1%\" already loaded!") % SoundName);
		throw std::exception(e.c_str());
		return false;
	}
	m_SoundMap[SoundName] = SOUNDBFRPTR(new sf::SoundBuffer());
	if(m_SoundMap[SoundName]->loadFromFile(FileName) == false)
	{
		std::string e = boost::str( boost::format("Failed to load soundfile \"%1%\".") % FileName);
		throw std::exception(e.c_str());
		return false;
	}
	return true;
}

bool CSAudioManager::LoadMusic(std::string FileName, std::string MusicName)
{
	if(m_MusicMap.find(MusicName) != m_MusicMap.end())
	{
		std::string e = boost::str( boost::format("Music: \"%1%\" already loaded!") % MusicName);
		throw std::exception(e.c_str());
		return false;
	}
	m_MusicMap[MusicName] = MUSICPTR(new sf::Music());
	if(m_MusicMap[MusicName]->openFromFile(FileName.c_str()) == false)
	{
		std::string e = boost::str( boost::format("Failed to load music file \"%1%\".") % FileName);
		throw std::exception(e.c_str());
		return false;
	}
	return true;
}

SOUNDPTR CSAudioManager::GetSound(std::string SoundName)
{
	if(m_SoundMap.find(SoundName) == m_SoundMap.end())
	{
		std::string e = boost::str( boost::format("Sound: \"%1%\" not loaded!") % SoundName);
		throw std::exception(e.c_str());
		return NULL;
	}

	return SOUNDPTR(new sf::Sound((*m_SoundMap[SoundName].get())));
}

MUSICPTR CSAudioManager::GetMusic(std::string MusicName)
{
	if(m_MusicMap.find(MusicName) == m_MusicMap.end())
	{
		std::string e = boost::str( boost::format("Music: \"%1%\" not loaded!") % MusicName);
		throw std::exception(e.c_str());
		return NULL;
	}

	return m_MusicMap[MusicName];
}

void CSAudioManager::Clear()
{
	m_SoundMap.clear();
	m_MusicMap.clear();
	delete m_Instance;
	m_Instance = NULL;
}