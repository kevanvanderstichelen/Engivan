#pragma once
#include "ResourceManager.h"

struct SDL_Texture;
namespace dae
{
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D & other ) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		inline const float GetWidth() const noexcept { return m_Width; };
		inline const float GetHeight() const noexcept { return m_Height; };
		inline const uint GetID() const noexcept { return m_Id; };

	private:
		friend class ResourceManager;
		Texture2D(const uint id, const float width, const float height);

		SDL_Texture* m_Texture;
		const uint m_Id;
		const float m_Width;
		const float m_Height;
	};
}
