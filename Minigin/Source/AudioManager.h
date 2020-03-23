#pragma once
#include <map>
#include "Utilities.h"
#include "SoundStream.h"
#include "SoundEffect.h"
#include "Devlog.h"

namespace dae
{

#pragma region ALL AUDIO SERVICES

	class Audio
	{
	public:
		Audio();
		~Audio();
		virtual void PlaySFX(const uint soundID, const uint volume = 1, const uint loops = 0) = 0;
		virtual void PlayMusic(const uint musicID, const bool loop = false) = 0;

		void AddSFX(const std::string& path, const uint id);
		void AddMusic(const std::string& path, const uint id);
		void StopMusic();
		void PauseMusic();
		void ResumeMusic();
		int GetVolumeMusic();
		void SetVolumeMusic(const uint value);
		void StopAllSoundEffect();
		void PauseAllSoundEffect();
		void ResumeAllSoundEffect();

	protected:
		std::map<uint, SoundStream*> m_pMusics;
		std::map<uint, SoundEffect*> m_pSoundEffects;

	};

	class NullAudio final : public Audio
	{
	public:
		virtual void PlaySFX(const uint, const uint, const uint) override {};
		virtual void PlayMusic(const uint, const bool) override {};
	};

	class DefaultAudio final : public Audio
	{
	public:
		virtual void PlaySFX(const uint effectID, const uint volume, const uint loops) override
		{
			const auto it = m_pSoundEffects.find(effectID);
			if (it == m_pSoundEffects.end())
			{
				Devlog::GetInstance().PrintWarning("DefaultAudio::PlaySFX() effect ID" + std::to_string(effectID) + " not found!");
				return;
			}
			it->second->Play(loops);
			it->second->SetVolume(volume);
		};
		virtual void PlayMusic(const uint musicID, const bool loop) override
		{
			const auto it = m_pMusics.find(musicID);
			if (it == m_pMusics.end())
			{
				Devlog::GetInstance().PrintWarning("DefaultAudio::PlayMusic() music ID" + std::to_string(musicID) + " not found!");
				return;
			}
			it->second->Play(loop);
		};

	};


	class LoggedAudio final : public Audio
	{
	public:
		LoggedAudio() = default;
		virtual void PlaySFX(const uint effectID, const uint volume, const uint loops) override
		{
			const auto it = m_pSoundEffects.find(effectID);
			if (it == m_pSoundEffects.end())
			{
				Devlog::GetInstance().PrintWarning("DefaultAudio::PlaySFX() effect ID" + std::to_string(effectID) + " not found!");
				return;
			}
			it->second->Play(loops);
			it->second->SetVolume(volume);
			Devlog::GetInstance().Print("LoggedAudio::Sound Effect @ " + it->second->GetPath() + " played with " + std::to_string(effectID) + " ID.");
		};
		virtual void PlayMusic(const uint musicID, const bool loop) override
		{
			const auto it = m_pMusics.find(musicID);
			if (it == m_pMusics.end())
			{
				Devlog::GetInstance().PrintWarning("DefaultAudio::PlayMusic() music ID" + std::to_string(musicID) + " not found!");
				return;
			}
			it->second->Play(loop);
			Devlog::GetInstance().Print("LoggedAudio::Sound Effect @ " + it->second->GetPath() + " played with " + std::to_string(musicID) + " ID.");
		};

	private:

	};

#pragma endregion ALL AUDIO SERVICES

	class AudioManager
	{
	public:
		static Audio& GetService() { return *m_pService; }
		static void Initialize() { m_pService = &m_NullService; }
		static void Provide(Audio* pService)
		{
			if (pService == nullptr)
				m_pService = &m_NullService;
			else
				m_pService = pService;
		}
		static void Reset(){ SAFE_DELETE(m_pService); }

	private:
		static Audio* m_pService;
		static NullAudio m_NullService;
	};

}
