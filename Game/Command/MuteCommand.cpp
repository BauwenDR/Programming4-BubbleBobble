#include "MuteCommand.hpp"

#include "ServiceLocator.hpp"

void MuteCommand::Execute()
{
    dae::ServiceLocator::GetSoundSystem().MuteSound();
}
