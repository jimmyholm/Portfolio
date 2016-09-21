#include "CSTextureManager.h"
#include <exception>
#include <boost\format.hpp>
CSTextureManager* CSTextureManager::m_Instance = NULL;

CSTextureManager::CSTextureManager() {}

CSTextureManager* CSTextureManager::GetInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new CSTextureManager();
	}
	return m_Instance;
}

bool CSTextureManager::LoadTexture(std::string Name, std::string File)
{
	stdext::hash_map<std::string, TEXPTR>::iterator it = m_TextureMap.find(Name);
	if(it != m_TextureMap.end())
	{
		std::string e = boost::str(boost::format("Texture name \"%1%\" already loaded.") % Name);
		throw(std::exception(e.c_str()));
		return false;
	}
	TEXPTR texture(new sf::Texture());
	if(texture.get()->loadFromFile(File.c_str()) == false)
	{
		std::string e = boost::str(boost::format("Failed to load texture from file \"%1%\".") % File);
		throw(std::exception(e.c_str()));
		return false;
	}
	m_TextureMap[Name] = texture;
	return true;
}
bool CSTextureManager::LoadTexture(std::string Name, const void* Data, std::size_t Size)
{
	stdext::hash_map<std::string, TEXPTR>::iterator it = m_TextureMap.find(Name);
	if(it != m_TextureMap.end())
	{
		std::string e = boost::str(boost::format("Texture name \"%1%\" already loaded.") % Name);
		throw(std::exception(e.c_str()));
		return false;
	}
	TEXPTR texture(new sf::Texture());
	if(texture.get()->loadFromMemory(Data, Size) == false)
	{
		throw(std::exception("Failed to load texture from memory!"));
		return false;
	}
	m_TextureMap[Name] = texture;
	return true;
}
bool CSTextureManager::LoadTexture(std::string Name, sf::InputStream& Stream)
{
	stdext::hash_map<std::string, TEXPTR>::iterator it = m_TextureMap.find(Name);
	if(it != m_TextureMap.end())
	{
		std::string e = boost::str(boost::format("Texture name \"%1%\" already loaded.") % Name);
		throw(std::exception(e.c_str()));
		return false;
	}
	TEXPTR texture(new sf::Texture());
	if(texture.get()->loadFromStream(Stream) == false)
	{
		throw(std::exception("Failed to load texture from stream!"));
		return false;
	}
	m_TextureMap[Name] = texture;
	return true;
}
bool CSTextureManager::LoadTexture(std::string Name, const sf::Image& Image)
{
	stdext::hash_map<std::string, TEXPTR>::iterator it = m_TextureMap.find(Name);
	if(it != m_TextureMap.end())
	{
		std::string e = boost::str(boost::format("Texture name \"%1%\" already loaded.") % Name);
		throw(std::exception(e.c_str()));
		return false;
	}
	TEXPTR texture(new sf::Texture());
	if(texture.get()->loadFromImage(Image) == false)
	{
		throw(std::exception("Failed to load texture from image!"));
		return false;
	}
	m_TextureMap[Name] = texture;
	return true;
}

TEXPTR CSTextureManager::GetTexture(std::string Name)
{
	stdext::hash_map<std::string, TEXPTR>::iterator it = m_TextureMap.find(Name);
	if(it == m_TextureMap.end())
	{
		std::string e = boost::str(boost::format("Texture name \"%1%\" not loaded.") % Name);
		throw(std::exception(e.c_str()));
		return NULL;
	}
	return m_TextureMap[Name];
}

void CSTextureManager::UnloadTexture(std::string Name)
{
	stdext::hash_map<std::string, TEXPTR>::iterator it = m_TextureMap.find(Name);
	if(it == m_TextureMap.end())
	{
		return;
	}
	m_TextureMap.erase(it);
	return;
}

void CSTextureManager::Clear()
{
	m_TextureMap.clear();
	delete m_Instance;
	m_Instance = NULL;
}

bool CSTextureManager::IsTextureLoaded(std::string Name)
{
	return (m_TextureMap.find(Name) != m_TextureMap.end());
}