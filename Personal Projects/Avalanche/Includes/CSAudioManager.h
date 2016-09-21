#ifndef SFMLG_CSAUDIOMANAGER_H
#define SFMLG_CSAUDIOMANAGER_H
#include <SFML\Audio.hpp>
#include <hash_map>
#include <boost\smart_ptr.hpp>
#include <boost\format.hpp>

typedef boost::shared_ptr<sf::Sound> SOUNDPTR;
typedef boost::shared_ptr<sf::SoundBuffer> SOUNDBFRPTR;
typedef boost::shared_ptr<sf::Music> MUSICPTR;

class CSAudioManager
{
	private:
		CSAudioManager();
		stdext::hash_map<std::string, SOUNDBFRPTR> m_SoundMap;
		stdext::hash_map<std::string, MUSICPTR> m_MusicMap;
		static CSAudioManager* m_Instance;

	public:
		static CSAudioManager* GetInstance();

		bool LoadSound(std::string FileName, std::string SoundName);
		bool LoadMusic(std::string FileName, std::string MusicName);
		SOUNDPTR GetSound(std::string SoundName);
		MUSICPTR GetMusic(std::string MusicName);

		void Clear();

};

#endif