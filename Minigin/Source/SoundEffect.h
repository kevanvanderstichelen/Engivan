#pragma once
#pragma comment(lib, "SDL2_mixer.lib") 
#include <SDL_mixer.h>

namespace dae
{
	class SoundEffect
	{
	public:
		SoundEffect(const std::string path);
		~SoundEffect();

		SoundEffect(const SoundEffect& other) = delete;
		SoundEffect(SoundEffect&& other) noexcept = delete;
		SoundEffect& operator=(const SoundEffect& other) = delete;
		SoundEffect& operator=(SoundEffect&& other) noexcept = delete;

		void Play(int loops) const;
		void SetVolume(int value);
		int GetVolume() const;
		const std::string& GetPath() const;
	private:
		Mix_Chunk* m_pSoundEffect;
		const std::string m_Path;
	};


}
