#include "PlayerInputComponent.hpp"

#include <memory>

#include "InputManager.hpp"
#include "MoveCommand.hpp"

game::PlayerInputComponent::PlayerInputComponent(dae::GameObject &owner, float movesSpeed, int player)
    : GameComponent(owner)
      , m_moveUpCommand{std::make_unique<MoveCommand>(owner, movesSpeed, glm::vec3{0.0f, -1.0f, 0.0f})}
      , m_moveDownCommand{std::make_unique<MoveCommand>(owner, movesSpeed, glm::vec3{0.0f, 1.0f, 0.0f})}
      , m_moveLeftCommand{std::make_unique<MoveCommand>(owner, movesSpeed, glm::vec3{-1.0f, 0.0f, 0.0f})}
      , m_moveRightCommand{std::make_unique<MoveCommand>(owner, movesSpeed, glm::vec3{1.0f, 0.0f, 0.0f})}

{
    const auto kbUp{player == 0 ? SDLK_W : SDLK_UP};
    const auto kbDown{player == 0 ? SDLK_S : SDLK_DOWN};
    const auto kbLeft{player == 0 ? SDLK_A : SDLK_LEFT};
    const auto kbRight{player == 0 ? SDLK_D : SDLK_RIGHT};

    dae::InputManager::GetInstance().Bind(kbUp, dae::Input::CommandTrigger::KeyHeld, m_moveUpCommand.get());
    dae::InputManager::GetInstance().Bind(kbDown, dae::Input::CommandTrigger::KeyHeld, m_moveDownCommand.get());
    dae::InputManager::GetInstance().Bind(kbLeft, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(kbRight, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadUp, player, dae::Input::CommandTrigger::KeyHeld, m_moveUpCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadDown, player, dae::Input::CommandTrigger::KeyHeld, m_moveDownCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadLeft, player, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadRight, player, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());
}

game::PlayerInputComponent::~PlayerInputComponent()
{
    dae::InputManager::GetInstance().Unbind(m_moveUpCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveDownCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveRightCommand.get());
}


