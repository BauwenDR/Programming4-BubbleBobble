#ifndef MINIGIN_SOUNDSYSTEM_HPP
#define MINIGIN_SOUNDSYSTEM_HPP
#include <cstdint>

namespace dae::AudioQueue
{
    void PlaySound(uint32_t sound_id_hash, float volume);
};

#endif //MINIGIN_SOUNDSYSTEM_HPP
