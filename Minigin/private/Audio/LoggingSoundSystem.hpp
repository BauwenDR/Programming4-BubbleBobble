#ifndef MINIGIN_LOGGINGSOUNDSYSTEM_HPP
#define MINIGIN_LOGGINGSOUNDSYSTEM_HPP
#include <iostream>
#include <memory>

#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

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

            // TODO this kind of logging is not maintainable at all (same TODO as in Minigin.cpp)
#if _WIN32
            std::stringstream ss;
            ss << "Playing sound " << soundId << " at volume " << volume << '\n';
            OutputDebugString(ss.str().c_str());
#else
            std::cout << "Playing sound " << soundId << " at volume " << volume << '\n';
#endif

            m_soundSystem->PlaySound(soundId, volume);
        }

        void MuteSound() override
        {

            // TODO this kind of logging is not maintainable at all (same TODO as in Minigin.cpp)
#if _WIN32
            std::stringstream ss;
            ss << "(Un)muting all sound \n";
            OutputDebugString(ss.str().c_str());
#else
            std::cout << "(Un)muting all sound \n";
#endif

            m_soundSystem->MuteSound();
        }

    private:
        std::unique_ptr<ISoundSystem> m_soundSystem{};
    };
}

#endif //MINIGIN_LOGGINGSOUNDSYSTEM_HPP
