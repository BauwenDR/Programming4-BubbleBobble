#ifndef MINIGIN_ISOUNDSYSTEM_HPP
#define MINIGIN_ISOUNDSYSTEM_HPP
#include <cstdint>

namespace  dae
{
    class ISoundSystem
    {
    public:
        virtual void PlaySound(uint32_t soundId, float volume) = 0;
        virtual void MuteSound() = 0;

        virtual ~ISoundSystem() = default;
    };
}

#endif //MINIGIN_ISOUNDSYSTEM_HPP
