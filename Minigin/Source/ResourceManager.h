#pragma once
#include "Singleton.h"
#include <unordered_map>
namespace dae
{
	class Font;
	class Texture2D;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		Texture2D* LoadImageTexture(const std::string& file) const;
		Font* LoadFont(const std::string& file, unsigned int size) const;
		Texture2D* CreateFromSurface(SDL_Surface* pSurface) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
	};
}
