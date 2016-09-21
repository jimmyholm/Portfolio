#ifndef SFMLG_CSTEXTUREMANAGER_H
#define SFMLG_CSTEXTUREMANAGER_H
#include <SFML\Graphics.hpp>
#include <hash_map>
#include <boost/smart_ptr.hpp>
#include <string>
/*
CLASS:		CSTextureManager
PURPOSE:	Provide a way to load and catalogue textures and make sure the same texture name is loaded only once. 
			Smart Pointers are used to create a system where textures are not destroyed while still in use.
			Smart pointers provided via Boost.
*/
typedef boost::shared_ptr<sf::Texture> TEXPTR;

class CSTextureManager
{
	private:
		CSTextureManager();
		stdext::hash_map<std::string, TEXPTR> m_TextureMap;
		static CSTextureManager* m_Instance;
	public:
		static CSTextureManager* GetInstance();

		// Functions for loading a texture into the manager. Return true on success, return false on failure or if the name is already taken. Throws exceptions on error.
		bool LoadTexture(std::string Name, std::string File);
		bool LoadTexture(std::string Name, const void* Data, std::size_t Size);
		bool LoadTexture(std::string Name, sf::InputStream& Stream);
		bool LoadTexture(std::string Name, const sf::Image& Image);

		// Return a smart-pointer to a requested texture. Return NULL and throw an exception if the requested texture does not exist.
		TEXPTR GetTexture(std::string Name);

		// Unload a function by name. Never fails.
		void UnloadTexture(std::string Name);

		// Unload all loaded textures.
		void Clear();

		// Check if a specific texture name is loaded.
		bool IsTextureLoaded(std::string Name);
};

#endif // SFMLG_CSTEXTUREMANAGER_H