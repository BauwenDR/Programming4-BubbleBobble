#include "GameOver.hpp"

#include "GameState.hpp"
#include "Input/InputManager.hpp"
#include "Prefab/StagesManager.hpp"

void game::GameOver::Start()
{
    dae::InputManager::GetInstance().Bind(SDLK_DOWN, dae::Input::CommandTrigger::KeyUp, &m_mainMenu);
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::B, 0, dae::Input::CommandTrigger::KeyUp, &m_mainMenu);

    auto const records{GameState::GetInstance().GetHighScores()};
    float height{64.0f};
    for (auto const &record : records)
    {
        StagesManager::GetInstance().AddScoreDisplay(record, height);
        height += 8.0f;
    }
}

void game::GameOver::Update()
{
}

void game::GameOver::OnDelete()
{
    dae::InputManager::GetInstance().Unbind(&m_mainMenu);
}

game::GameOver::GameOver(dae::GameObject& owner)
    : GameComponent(owner)
{
}
