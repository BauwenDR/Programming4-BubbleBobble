#ifndef MINIGIN_LOGGINGSOUNDSYSTEM_HPP
#define MINIGIN_LOGGINGSOUNDSYSTEM_HPP
#include <iostream>
#include <memory>

#include "ISoundSystem.hpp"

namespace dae
{
    class LoggingSoundSystem final : public ISoundSystem
    {
    public:
        explicit LoggingSoundSystem(std::unique_ptr<ISoundSystem> soundSystem)
            : m_soundSystem(std::move(soundSystem))
        {
        }

        void PlaySound(uint32_t soundId, float volume) override
        {
            std::cout << "Playing sound " << soundId << "at volume " << volume << '\n';
            m_soundSystem->PlaySound(soundId, volume);
        }

    private:
        std::unique_ptr<ISoundSystem> m_soundSystem{};
    };
}

#endif //MINIGIN_LOGGINGSOUNDSYSTEM_HPP
