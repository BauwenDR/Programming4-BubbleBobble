#include "PlayerInputComponent.hpp"

#include <iostream>
#include <memory>

#include "Command/JumpCommand.hpp"
#include "Command/MoveCommand.hpp"
#include "Component/LivesScoreComponent.hpp"

#include "Component/PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Input/InputManager.hpp"
#include "GameObject.hpp"

void game::PlayerInputComponent::Start()
{
    m_livesScoreComponent = GetGameObject().GetComponent<LivesScoreComponent>();

    assert(m_livesScoreComponent != nullptr && "There was no lives component attached!");

    const auto kbLeft{player == 0 ? SDLK_A : SDLK_LEFT};
    const auto kbRight{player == 0 ? SDLK_D : SDLK_RIGHT};
    const auto kbJump{player == 0 ? SDLK_W : SDLK_UP};

    // const auto kbKill{player == 0 ? SDLK_C : SDLK_N};
    // const auto kbSmall{player == 0 ? SDLK_Z : SDLK_V};
    // const auto kbBig{player == 0 ? SDLK_X : SDLK_B};

    auto physics{GetGameObject().GetComponent<dae::PhysicsComponent>()};

    m_jumpCommand = std::make_unique<JumpCommand>(physics);
    m_moveLeftCommand = std::make_unique<MoveCommand>(physics, -1.0f);
    m_moveRightCommand = std::make_unique<MoveCommand>(physics, 1.0f);

    dae::InputManager::GetInstance().Bind(kbLeft, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(kbRight, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());

    dae::InputManager::GetInstance().Bind(kbJump, dae::Input::CommandTrigger::KeyDown, m_jumpCommand.get());

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadLeft, player, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadRight, player, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadUp, player, dae::Input::CommandTrigger::KeyHeld, m_jumpCommand.get());
}

game::PlayerInputComponent::PlayerInputComponent(dae::GameObject &owner, int player)
    : GameComponent(owner), player(player)
{
}

game::PlayerInputComponent::~PlayerInputComponent()
{
    // dae::InputManager::GetInstance().Unbind(m_increaseScoreCommandBig.get());
    // dae::InputManager::GetInstance().Unbind(m_increaseScoreCommandSmall.get());
    // dae::InputManager::GetInstance().Unbind(m_decreaseLivesCommand.get());

    dae::InputManager::GetInstance().Unbind(m_jumpCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveRightCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveLeftCommand.get());
}
