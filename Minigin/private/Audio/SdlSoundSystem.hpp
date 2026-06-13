#ifndef MINIGIN_SDLSOUNDSYSTEM_HPP
#define MINIGIN_SDLSOUNDSYSTEM_HPP
#include <memory>

#include "ISoundSystem.hpp"

namespace dae
{
    class SdlSoundSystem final : public ISoundSystem
    {
    public:
        void PlaySound(uint32_t soundId, float volume) override;
        void MuteSound() override;

        SdlSoundSystem();
        ~SdlSoundSystem() override;

    private:
        class Impl;
        std::unique_ptr<Impl> const m_impl{};
    };
}

#endif //MINIGIN_SDLSOUNDSYSTEM_HPP
