#ifndef MINIGIN_SOUNDSYSTEM_HPP
#define MINIGIN_SOUNDSYSTEM_HPP
#include <cstdint>
#include <string>

namespace dae::AudioQueue
{
    void LoadSound(uint32_t sound_id, std::string const &fileName);
    void PlaySound(uint32_t sound_id_hash, float volume);
};

#endif //MINIGIN_SOUNDSYSTEM_HPP
