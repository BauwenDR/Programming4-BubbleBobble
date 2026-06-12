#include "InGame.hpp"

#include "Input/InputManager.hpp"

void InGame::Start()
{
    dae::InputManager::GetInstance().Bind(SDLK_F1, dae::Input::CommandTrigger::KeyDown, &m_skipStage);
    dae::InputManager::GetInstance().Bind(SDLK_F2, dae::Input::CommandTrigger::KeyDown, &m_mute);
}

void InGame::OnDelete()
{
    dae::InputManager::GetInstance().Unbind(&m_mute);
    dae::InputManager::GetInstance().Unbind(&m_skipStage);
}

InGame::InGame(dae::GameObject& owner)
    : GameComponent(owner)
{
}
