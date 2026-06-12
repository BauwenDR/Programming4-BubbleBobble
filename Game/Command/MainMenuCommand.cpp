#include "MainMenuCommand.hpp"

#include "Prefab/StagesManager.hpp"

void game::MainMenuCommand::Execute()
{
    StagesManager::GetInstance().LoadSceneFromJson("MainMenu", false);
}
