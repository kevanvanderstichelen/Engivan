#pragma once
#include <SDL_mixer.h>
#include "MiniginPCH.h"

namespace dae
{
	class SoundStream
	{
	public:
		SoundStream(const std::string path);
		~SoundStream();

		SoundStream(const SoundStream& other) = delete;
		SoundStream(SoundStream&& other) noexcept = delete;
		SoundStream& operator=(const SoundStream& other) = delete;
		SoundStream& operator=(SoundStream&& other) noexcept = delete;

		void Play(bool loop) const;
		const std::string& GetPath() const;
	private:
		Mix_Music* m_pMusic;
		const std::string m_Path;
	};


}
