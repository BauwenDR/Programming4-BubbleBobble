#ifndef MINIGIN_SDLSOUNDSYSTEM_HPP
#define MINIGIN_SDLSOUNDSYSTEM_HPP
#include <memory>

#include "ISoundSystem.hpp"

namespace dae
{
    class SdlSoundSystem final : public ISoundSystem
    {
    public:
        void PreLoadSound(uint32_t uint32) override;
        void PlaySound(uint32_t soundId, float volume) override;

        ~SdlSoundSystem() override = default;

    private:
        class Impl;
        std::unique_ptr<Impl> m_impl{};
    };
}

#endif //MINIGIN_SDLSOUNDSYSTEM_HPP
