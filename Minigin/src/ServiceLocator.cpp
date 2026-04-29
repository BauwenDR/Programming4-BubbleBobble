#include "ServiceLocator.hpp"

#include "private/Audio/ISoundSystem.hpp"
#include "private/Audio/NullSoundSystem.hpp"

namespace
{
    std::unique_ptr<dae::ISoundSystem> m_soundSystem{std::make_unique<dae::NullSoundSystem>()};
}

dae:: ISoundSystem &dae::ServiceLocator::GetSoundSystem()
{
    return *m_soundSystem;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem> &&soundSystem)
{
    m_soundSystem = std::move(soundSystem);
}
