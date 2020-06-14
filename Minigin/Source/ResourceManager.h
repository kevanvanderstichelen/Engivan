#pragma once
#include "Singleton.h"
#include <unordered_map>
namespace dae
{
	enum class TextureFilter
	{
		Default,
		Repeat
	};

	class Font;
	class Texture2D;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		~ResourceManager();
		Texture2D* LoadImageTexture(const std::string& file, const TextureFilter& filter = TextureFilter::Default) const;
		Font* LoadFont(const std::string& file, unsigned int size);
		Texture2D* CreateFromSurface(SDL_Surface* pSurface, const TextureFilter& filter = TextureFilter::Default) const;

		const std::string& GetDataPath() const { return m_DataPath; }
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
		std::vector<Font*> m_LoadedFonts;
	};
}
