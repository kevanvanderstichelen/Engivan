#include "MiniginPCH.h"
#include "SoundEffect.h"
#pragma comment(lib, "SDL2_mixer.lib") 
#include <SDL_mixer.h>

#include "Devlog.h"

dae::SoundEffect::SoundEffect(const std::string path)
	:m_pSoundEffect(Mix_LoadWAV(path.c_str()))
	,m_Path(path)
{
	if (m_pSoundEffect == nullptr)
	{
		Devlog::GetInstance().PrintError("SoundEffect::SoundEffect() failed to load " + path + " " + Mix_GetError());
	}
}

dae::SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_pSoundEffect);
	m_pSoundEffect = nullptr;
}

void dae::SoundEffect::Play(int loops) const
{
	if (m_pSoundEffect)
	{
		int result = Mix_PlayChannel( -1, m_pSoundEffect, loops);
		if (result != 0)
		{
			dae::Devlog::GetInstance().PrintWarning("SoundEffect::Play() Failed to play " + m_Path);
		}
	}
	else
	{
		dae::Devlog::GetInstance().PrintWarning("SoundEffect::Play() " + m_Path + " not valid (m_pSoundEffect is nullptr)!");
	}
}

void dae::SoundEffect::SetVolume(int value)
{
	if (m_pSoundEffect)
		Mix_VolumeChunk(m_pSoundEffect, value);
	else
		dae::Devlog::GetInstance().PrintWarning("SoundEffect::Play() " + m_Path + " not valid (m_pSoundEffect is nullptr)!");

}

int dae::SoundEffect::GetVolume() const
{
	return m_pSoundEffect ? Mix_VolumeChunk(m_pSoundEffect, -1) : INFINITE;
}

const std::string& dae::SoundEffect::GetPath() const
{
	return m_Path;
}
