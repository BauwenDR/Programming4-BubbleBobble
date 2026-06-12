#include "InGame.hpp"

#include "Component/LivesScoreComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Input/InputManager.hpp"
#include "Prefab/StagesManager.hpp"

void game::InGame::Start()
{
    dae::InputManager::GetInstance().Bind(SDLK_F1, dae::Input::CommandTrigger::KeyDown, &m_skipStage);
    dae::InputManager::GetInstance().Bind(SDLK_F2, dae::Input::CommandTrigger::KeyDown, &m_mute);

    dae::EventManager::GetInstance().AttachHandler(dae::sdbm_hash("player_died"), this);
}

void game::InGame::OnDelete()
{
    dae::EventManager::GetInstance().DetachHandler(this);

    dae::InputManager::GetInstance().Unbind(&m_mute);
    dae::InputManager::GetInstance().Unbind(&m_skipStage);
}

void game::InGame::HandleEvent(uint32_t event)
{
    if (event != dae::sdbm_hash("player_died")) return;

    auto &players{StagesManager::GetInstance().GetPlayers()};
    bool allDead{std::ranges::all_of(players, [](auto const &player) { return player.m_livesScore->GetLives() < 0; })};

    if (!allDead) return;

    StagesManager::GetInstance().LoadSceneFromJson("GameOver", false);
}

game::InGame::InGame(dae::GameObject& owner)
    : GameComponent(owner)
{
}
