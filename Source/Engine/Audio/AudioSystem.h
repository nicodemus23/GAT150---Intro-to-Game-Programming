#pragma once
#include <fmod/core/inc/fmod.hpp>
#include <string>
#include <map>

namespace kiko
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;
		~AudioSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		void AddAudio(const std::string& name, const std::string& filename);
		void PlayOneShot(const std::string& name, bool loop = false);

	private:
		FMOD::System* m_fmodSystem = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;

	};


	// this is just a variable declaration. The object(function) definition is actually in .cpp 
	extern AudioSystem g_audioSystem;
}

