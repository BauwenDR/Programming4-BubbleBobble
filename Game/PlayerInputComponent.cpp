#include "PlayerInputComponent.hpp"

#include <memory>

#include "DecreaseLivesCommand.hpp"
#include "IncreaseScoreCommand.hpp"
#include "LivesScoreComponent.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "MoveCommand.hpp"

void game::PlayerInputComponent::Start()
{
    m_livesScoreComponent = GetGameObject().GetComponent<LivesScoreComponent>();

    assert(m_livesScoreComponent != nullptr && "There was no lives component attached!");
}

game::PlayerInputComponent::PlayerInputComponent(dae::GameObject &owner, float movesSpeed, int player)
    : GameComponent(owner)
      , m_moveUpCommand{std::make_unique<MoveCommand>(owner, movesSpeed, glm::vec3{0.0f, -1.0f, 0.0f})}
      , m_moveDownCommand{std::make_unique<MoveCommand>(owner, movesSpeed, glm::vec3{0.0f, 1.0f, 0.0f})}
      , m_moveLeftCommand{std::make_unique<MoveCommand>(owner, movesSpeed, glm::vec3{-1.0f, 0.0f, 0.0f})}
      , m_moveRightCommand{std::make_unique<MoveCommand>(owner, movesSpeed, glm::vec3{1.0f, 0.0f, 0.0f})}
      , m_decreaseLivesCommand(std::make_unique<DecreaseLivesCommand>(owner))
      , m_increaseScoreCommandSmall(std::make_unique<IncreaseScoreCommand>(owner, false))
      , m_increaseScoreCommandBig(std::make_unique<IncreaseScoreCommand>(owner, true))
{
    const auto kbUp{player == 0 ? SDLK_W : SDLK_UP};
    const auto kbDown{player == 0 ? SDLK_S : SDLK_DOWN};
    const auto kbLeft{player == 0 ? SDLK_A : SDLK_LEFT};
    const auto kbRight{player == 0 ? SDLK_D : SDLK_RIGHT};

    const auto kbKill{player == 0 ? SDLK_C : SDLK_N};
    const auto kbSmall{player == 0 ? SDLK_Z : SDLK_V};
    const auto kbBig{player == 0 ? SDLK_X : SDLK_B};

    dae::InputManager::GetInstance().Bind(kbUp, dae::Input::CommandTrigger::KeyHeld, m_moveUpCommand.get());
    dae::InputManager::GetInstance().Bind(kbDown, dae::Input::CommandTrigger::KeyHeld, m_moveDownCommand.get());
    dae::InputManager::GetInstance().Bind(kbLeft, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(kbRight, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());
    dae::InputManager::GetInstance().Bind(kbKill, dae::Input::CommandTrigger::KeyUp, m_decreaseLivesCommand.get());
    dae::InputManager::GetInstance().Bind(kbSmall, dae::Input::CommandTrigger::KeyDown, m_increaseScoreCommandSmall.get());
    dae::InputManager::GetInstance().Bind(kbBig, dae::Input::CommandTrigger::KeyDown, m_increaseScoreCommandBig.get());

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadUp, player, dae::Input::CommandTrigger::KeyHeld, m_moveUpCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadDown, player, dae::Input::CommandTrigger::KeyHeld, m_moveDownCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadLeft, player, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadRight, player, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::X, player, dae::Input::CommandTrigger::KeyUp, m_decreaseLivesCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::A, player, dae::Input::CommandTrigger::KeyDown, m_increaseScoreCommandSmall.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::B, player, dae::Input::CommandTrigger::KeyDown, m_increaseScoreCommandBig.get());
}

game::PlayerInputComponent::~PlayerInputComponent()
{
    dae::InputManager::GetInstance().Unbind(m_increaseScoreCommandBig.get());
    dae::InputManager::GetInstance().Unbind(m_increaseScoreCommandSmall.get());
    dae::InputManager::GetInstance().Unbind(m_decreaseLivesCommand.get());

    dae::InputManager::GetInstance().Unbind(m_moveRightCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveDownCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveUpCommand.get());
}
