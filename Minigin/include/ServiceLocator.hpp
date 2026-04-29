#ifndef MINIGIN_SERVICELOCATOR_HPP
#define MINIGIN_SERVICELOCATOR_HPP
#include <memory>

#include "private/Audio/ISoundSystem.hpp"

namespace dae
{
    namespace ServiceLocator {
        ISoundSystem &GetSoundSystem();
        void RegisterSoundSystem(std::unique_ptr<ISoundSystem> &&soundSystem);
    };
}

#endif //MINIGIN_SERVICELOCATOR_HPP
