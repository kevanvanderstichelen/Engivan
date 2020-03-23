#include "MiniginPCH.h"
#include "AudioManager.h"
#include "Devlog.h"
#include "SoundEffect.h"
#include <SDL_mixer.h>

dae::Audio* dae::AudioManager::m_pService{ nullptr };
dae::NullAudio dae::AudioManager::m_NullService{};

dae::Audio::Audio()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		dae::Devlog::GetInstance().PrintError("Audio::Audio() SDL_Mixer OpenAudio error. ");
	}
}

dae::Audio::~Audio()
{
	for (std::pair<uint, SoundStream*> music : m_pMusics)
	{
		SAFE_DELETE(music.second);
	}

	for (std::pair<uint, SoundEffect*> sfx : m_pSoundEffects)
	{
		SAFE_DELETE(sfx.second);
	}

	Mix_Quit();
}

void dae::Audio::AddSFX(const std::string& path, const uint id)
{
	SoundEffect* soundEffect = new SoundEffect(path);

	std::pair<std::map<uint, SoundEffect*>::iterator, bool> ret;
	ret = m_pSoundEffects.insert(std::pair<uint, SoundEffect*>(id, soundEffect));
	if (!ret.second)
	{
		dae::Devlog::GetInstance().PrintWarning("Audio::AddSFX " + path + " Already exist in AudioManager.");
	}
}

void dae::Audio::AddMusic(const std::string& path, const uint id)
{
	SoundStream* soundEffect = new SoundStream(path);

	std::pair<std::map<uint, SoundStream*>::iterator, bool> ret;
	ret = m_pMusics.insert(std::pair<uint, SoundStream*>(id, soundEffect));
	if (!ret.second)
	{
		dae::Devlog::GetInstance().PrintWarning("Audio::AddMusic " + path + " Already exist in AudioManager.");
	}
}

void dae::Audio::StopMusic()
{
	Mix_HaltMusic();
}

void dae::Audio::PauseMusic()
{
	Mix_PauseMusic();
}

void dae::Audio::ResumeMusic()
{
	Mix_ResumeMusic();
}

int dae::Audio::GetVolumeMusic()
{
	return Mix_VolumeMusic(-1);
}

void dae::Audio::SetVolumeMusic(const uint value)
{
	Mix_VolumeMusic(value);
}

void dae::Audio::StopAllSoundEffect()
{
	Mix_HaltChannel(-1);
}

void dae::Audio::PauseAllSoundEffect()
{
	Mix_Pause(-1);
}

void dae::Audio::ResumeAllSoundEffect()
{
	Mix_Resume(-1);
}
