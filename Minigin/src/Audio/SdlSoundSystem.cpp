#include "private/Audio/SdlSoundSystem.hpp"

#include <SDL3/SDL.h>

#include "Audio/AudioQueue.hpp"
#include "private/Audio/AudioQueue.hpp"
#include "Render/ResourceManager.hpp"

class dae::SdlSoundSystem::Impl
{
public:
    void PlaySound(uint32_t soundId, float volume) const;

    Impl();
};

void dae::SdlSoundSystem::Impl::PlaySound(uint32_t soundId, float volume) const
{
    SDL_AudioSpec wavSpec{};
    Uint32 wavLength{};
    Uint8 *wavBuffer{};

    if (!SDL_LoadWAV(ResourceManager::GetInstance().GetFilePath(AudioQueue::GetPathForId(soundId)).c_str(), &wavSpec, &wavBuffer, &wavLength))
    {
        return;
    }

    if (auto stream{SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &wavSpec, nullptr, nullptr)}; stream != nullptr)
    {
        SDL_SetAudioStreamGain(stream, volume);

        SDL_PutAudioStreamData(stream, wavBuffer, static_cast<int>(wavLength));
        SDL_ResumeAudioStreamDevice(stream);
    }

    SDL_free(wavBuffer);
}

dae::SdlSoundSystem::Impl::Impl()
{
    SDL_InitSubSystem(SDL_INIT_AUDIO);
}

void dae::SdlSoundSystem::PlaySound(uint32_t soundId, float volume)
{
    m_impl->PlaySound(soundId, volume);
}

dae::SdlSoundSystem::SdlSoundSystem()
    : m_impl(std::make_unique<Impl>())
{
}

dae::SdlSoundSystem::~SdlSoundSystem()
{
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
