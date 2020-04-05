#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
	glDeleteTextures(1, &m_Id);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
	:m_Id(0), m_Width(0), m_Height(0)
{
	m_Texture = texture;
}

//PRIVATE: Accessable by ResourceManager (friend class)
dae::Texture2D::Texture2D(const uint id, const float width, const float height)
	:m_Id(id), m_Width(width), m_Height(height), m_Texture(nullptr)
{
}
