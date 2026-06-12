#include "MainMenu.hpp"

#include "Input/InputManager.hpp"

void game::MainMenu::Start()
{
    auto const &inputManager{dae::InputManager::GetInstance()};

    inputManager.Bind(SDLK_LEFT, dae::Input::CommandTrigger::KeyUp, &m_startSingleGameCommand);
    inputManager.Bind(SDLK_UP, dae::Input::CommandTrigger::KeyUp, &m_startCoopGameCommand);
    inputManager.Bind(SDLK_RIGHT, dae::Input::CommandTrigger::KeyUp, &m_startVersusGameCommand);

    inputManager.Bind(dae::Input::ControllerKey::DpadLeft, 0, dae::Input::CommandTrigger::KeyUp, &m_startSingleGameCommand);
    inputManager.Bind(dae::Input::ControllerKey::DpadUp, 0, dae::Input::CommandTrigger::KeyUp, &m_startCoopGameCommand);
    inputManager.Bind(dae::Input::ControllerKey::DpadRight, 0, dae::Input::CommandTrigger::KeyUp, &m_startVersusGameCommand);

    GameState::GetInstance().LoadHighScore();
}

void game::MainMenu::OnDelete()
{
    auto const &inputManager{dae::InputManager::GetInstance()};

    inputManager.Unbind(&m_startVersusGameCommand);
    inputManager.Unbind(&m_startCoopGameCommand);
    inputManager.Unbind(&m_startSingleGameCommand);
}

game::MainMenu::MainMenu(dae::GameObject &owner)
    : GameComponent(owner)
      , m_startSingleGameCommand(GameType::Single)
      , m_startCoopGameCommand(GameType::Coop)
      , m_startVersusGameCommand(GameType::Versus)
{
}
