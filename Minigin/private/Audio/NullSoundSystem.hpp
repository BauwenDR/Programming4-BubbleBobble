#ifndef MINIGIN_NULLSOUNDSYSTEM_HPP
#define MINIGIN_NULLSOUNDSYSTEM_HPP
#include "ISoundSystem.hpp"

#include <iostream>

namespace dae
{
    class NullSoundSystem final : public ISoundSystem
    {
    public:
        void PreLoadSound(uint32_t sound_id) override
        {
            std::cerr << "Tried pre-loading sound " << sound_id << " while no sound system was attached!\n";
        }

        void PlaySound(uint32_t sound_id, float) override
        {
            std::cerr << "Tried playing sound " << sound_id << " while no sound system was attached!\n";
        }

        ~NullSoundSystem() override = default;
    };
}

#endif //MINIGIN_NULLSOUNDSYSTEM_HPP
