#include "MiniginPCH.h"
#include "SoundStream.h"
#pragma comment(lib, "SDL2_mixer.lib") 
#include <SDL_mixer.h>
#include "Devlog.h"

dae::SoundStream::SoundStream(const std::string path) : m_Path(path) 
{
	m_pMusic = Mix_LoadMUS(path.c_str());
	if (!m_pMusic)
	{
		dae::Devlog::GetInstance().PrintError("SoundStream::Play() " + path + " Failed to load! + " + Mix_GetError());
	}
}

dae::SoundStream::~SoundStream()
{
	Mix_FreeMusic(m_pMusic);
	m_pMusic = nullptr;
}

void dae::SoundStream::Play(bool loop) const
{
	if (m_pMusic != nullptr)
	{
		int result = Mix_PlayMusic(m_pMusic, loop ? -1 : 1);
		if (result != 0)
		{
			dae::Devlog::GetInstance().PrintWarning("SoundStream::Play() Failed to play " + m_Path);
		}
	}
	else
	{
		dae::Devlog::GetInstance().PrintWarning("SoundStream::Play() " + m_Path + " not valid (m_pMusic is nullptr)!");
	}
}

const std::string& dae::SoundStream::GetPath() const
{
	return m_Path;
}
