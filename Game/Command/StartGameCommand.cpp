#include "StartGameCommand.hpp"

#include "Prefab/StagesManager.hpp"

void game::StartGameCommand::Execute() {
    GameManager::GetInstance().CurrentType = m_gameType;
    StagesManager::GetInstance().LoadStageFromJson(1, false);
}

game::StartGameCommand::StartGameCommand(GameType type)
    : m_gameType(type)
{
}
