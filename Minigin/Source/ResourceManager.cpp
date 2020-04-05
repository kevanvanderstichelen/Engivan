#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Devlog.h"

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

//Generates OpenGL type texture, returns new pointer of the texture
dae::Texture2D* dae::ResourceManager::LoadImageTexture(const std::string& file) const
{
	SDL_Surface* pSurface = IMG_Load(file.c_str());
	if (!pSurface)
	{
		DEBUGLOG.PrintError("ResourceManager::LoadTexture() Error creating from path: " + file);
		return nullptr;
	}
	Texture2D* texture = CreateFromSurface(pSurface);
	SDL_FreeSurface(pSurface);
	return texture;
}

dae::Font* dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return new Font(m_DataPath + file, size);
}

//Generates dae::Texture2D
dae::Texture2D* dae::ResourceManager::CreateFromSurface(SDL_Surface* pSurface) const
{
	//SOURCE: http://web.archive.org/web/20131228023100/http://content.gpwiki.org/SDL:Tutorials:Using_SDL_with_OpenGL

	//Get width & height of surface
	const float textureWidth = float(pSurface->w);
	const float textureHeight = float(pSurface->h);

	//Get color format from pSurface -> OpenGL
	GLenum textureFormat;
	if (pSurface->format->BytesPerPixel == 4) 
		textureFormat = (pSurface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
	else 
		textureFormat = (pSurface->format->Rmask == 0x000000ff) ? GL_RGB : GL_BGR;

	//Generate texture returns back id and binding
	uint textureID = 0;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Check Error
	if (glGetError() != GL_NO_ERROR)
		DEBUGLOG.PrintError("ResourceManager::CreateFromSurface, error binding textures, id = " + glGetError());
	
	//Specify texture's data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, textureFormat, GL_UNSIGNED_BYTE, pSurface->pixels);
	
	//Magnification filters (streching properties)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return new Texture2D(textureID, textureWidth, textureHeight);
}
