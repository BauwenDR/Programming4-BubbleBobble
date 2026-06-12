#include "SkipStageCommand.hpp"

#include "Prefab/StagesManager.hpp"

void SkipStageCommand::Execute()
{
    game::StagesManager::GetInstance().LoadNextStageFromJson();
}
