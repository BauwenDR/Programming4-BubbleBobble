#include "PlayerInputComponent.hpp"

#include <iostream>
#include <memory>

#include "DecreaseLivesCommand.hpp"
#include "IncreaseScoreCommand.hpp"
#include "LivesScoreComponent.hpp"
#include "GameObject.hpp"
#include "GravityComponent.hpp"
#include "InputManager.hpp"
#include "JumpCommand.hpp"
#include "MoveCommand.hpp"
#include "Sdbm.hpp"

void game::PlayerInputComponent::Start()
{
    m_livesScoreComponent = GetGameObject().GetComponent<LivesScoreComponent>();

    assert(m_livesScoreComponent != nullptr && "There was no lives component attached!");

    const auto kbLeft{player == 0 ? SDLK_A : SDLK_LEFT};
    const auto kbRight{player == 0 ? SDLK_D : SDLK_RIGHT};

    const auto kbKill{player == 0 ? SDLK_C : SDLK_N};
    const auto kbSmall{player == 0 ? SDLK_Z : SDLK_V};
    const auto kbBig{player == 0 ? SDLK_X : SDLK_B};

    m_moveLeftCommand = std::make_unique<MoveCommand>(GetGameObject(), movesSpeed, glm::vec3{-1.0f, 0.0f, 0.0f});
    m_moveRightCommand = std::make_unique<MoveCommand>(GetGameObject(), movesSpeed, glm::vec3{1.0f, 0.0f, 0.0f});
    m_decreaseLivesCommand = std::make_unique<DecreaseLivesCommand>(GetGameObject());
    m_increaseScoreCommandSmall = std::make_unique<IncreaseScoreCommand>(GetGameObject(), false);
    m_increaseScoreCommandBig = std::make_unique<IncreaseScoreCommand>(GetGameObject(), true);
    m_jumpCommand = std::make_unique<JumpCommand>(*GetGameObject().GetComponent<dae::GravityComponent>());

    dae::InputManager::GetInstance().Bind(kbLeft, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(kbRight, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());
    dae::InputManager::GetInstance().Bind(kbKill, dae::Input::CommandTrigger::KeyUp, m_decreaseLivesCommand.get());
    dae::InputManager::GetInstance().Bind(kbSmall, dae::Input::CommandTrigger::KeyDown, m_increaseScoreCommandSmall.get());
    dae::InputManager::GetInstance().Bind(kbBig, dae::Input::CommandTrigger::KeyDown, m_increaseScoreCommandBig.get());

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadLeft, player, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadRight, player, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::X, player, dae::Input::CommandTrigger::KeyUp, m_decreaseLivesCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::A, player, dae::Input::CommandTrigger::KeyDown, m_increaseScoreCommandSmall.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::B, player, dae::Input::CommandTrigger::KeyDown, m_increaseScoreCommandBig.get());

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadUp, player, dae::Input::CommandTrigger::KeyHeld, m_jumpCommand.get());
}

void game::PlayerInputComponent::Notify(const dae::GameObject &, uint32_t event, const dae::ObserverData *)
{
    switch (event)
    {
        case dae::sdbm_hash("on_collision_enter"):
            std::cout << "Collision enter\n";
            break;

        case dae::sdbm_hash("on_collision_exit"):
            std::cout << "Collision exit\n";
            break;
    }
}

game::PlayerInputComponent::PlayerInputComponent(dae::GameObject &owner, float movesSpeed, int player)
    : GameComponent(owner), player(player), movesSpeed(movesSpeed)
{
    GetGameObject().AddObserver(this);
}

game::PlayerInputComponent::~PlayerInputComponent()
{
    dae::InputManager::GetInstance().Unbind(m_increaseScoreCommandBig.get());
    dae::InputManager::GetInstance().Unbind(m_increaseScoreCommandSmall.get());
    dae::InputManager::GetInstance().Unbind(m_decreaseLivesCommand.get());

    dae::InputManager::GetInstance().Unbind(m_moveRightCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveLeftCommand.get());
}
