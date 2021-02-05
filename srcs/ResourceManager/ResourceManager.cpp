#include "ResourceManager.hpp"

FontList	ResourceManager::mFontResources = FontList();
TextureList	ResourceManager::mTextureResources = TextureList();
SoundBufferList ResourceManager::mSoundBufferResources = SoundBufferList();

ResourceManager::ResourceManager(/* args */)
{

}

ResourceManager::~ResourceManager()
{

}

/**
 * To be extended to sf::texture, sf::audio, sf::image etc...
 **/

sf::Font		*ResourceManager::LoadFont(std::string tPath)
{
	sf::Font	*font = NULL;

	if (mFontResources.count(tPath))
		return (sf::Font *)(mFontResources[tPath].get());
	try
	{
		font = new sf::Font();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Failed to load font: " << tPath << std::endl;
		std::cerr << e.what() << '\n';
		return (NULL);
	}
	font->loadFromFile(tPath);
	mFontResources[tPath] = std::shared_ptr<sf::Font>(font);
	return (font);
}

sf::Texture		*ResourceManager::LoadTexture(std::string tPath)
{
	sf::Texture	*texture = NULL;

	if (mTextureResources.count(tPath))
		return (sf::Texture *)(mTextureResources[tPath].get());
	try
	{
		texture = new sf::Texture();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Failed to load texture: " << tPath << std::endl;
		std::cerr << e.what() << '\n';
		return (NULL);
	}
	texture->loadFromFile(tPath);
	mTextureResources[tPath] = std::shared_ptr<sf::Texture>(texture);
	return (texture);
}

sf::SoundBuffer		*ResourceManager::LoadSoundBuffer(std::string tPath)
{
	sf::SoundBuffer	*soundbuffer = NULL;

	if (mSoundBufferResources.count(tPath))
		return (sf::SoundBuffer *)(mSoundBufferResources[tPath].get());
	try
	{
		soundbuffer = new sf::SoundBuffer();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Failed to load SoundBuffer: " << tPath << std::endl;
		std::cerr << e.what() << '\n';
		return (NULL);
	}
	soundbuffer->loadFromFile(tPath);
	mSoundBufferResources[tPath] = std::shared_ptr<sf::SoundBuffer>(soundbuffer);
	return (soundbuffer);
}