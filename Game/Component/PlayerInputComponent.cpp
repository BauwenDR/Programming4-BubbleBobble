#include "PlayerInputComponent.hpp"

#include <memory>

#include "Command/JumpCommand.hpp"
#include "Command/MoveCommand.hpp"
#include "Component/LivesScoreComponent.hpp"

#include "PhysicsComponent.hpp"
#include "Input/InputManager.hpp"
#include "GameObject.hpp"
#include "Command/SpawnBubbleCommand.hpp"

void game::PlayerInputComponent::Start()
{
    using enum dae::Input::CommandTrigger;
    using enum dae::Input::ControllerKey;

    const auto kbLeft{m_player == 0 ? SDLK_A : SDLK_LEFT};
    const auto kbRight{m_player == 0 ? SDLK_D : SDLK_RIGHT};
    const auto kbJump{m_player == 0 ? SDLK_Z : SDLK_UP};
    const auto kbAttack{m_player == 0 ? SDLK_X : SDLK_DOWN};

    auto physics{GetGameObject().GetComponent<PhysicsComponent>()};

    m_jumpCommand = std::make_unique<JumpCommand>(physics);
    m_attackCommand = std::make_unique<SpawnProjectileCommand>(&GetGameObject(), physics, m_player, m_isEnemy);
    m_moveLeftCommand = std::make_unique<MoveCommand>(physics, -1.0f);
    m_moveRightCommand = std::make_unique<MoveCommand>(physics, 1.0f);

    dae::InputManager::GetInstance().Bind(kbLeft, KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(kbRight, KeyHeld, m_moveRightCommand.get());

    dae::InputManager::GetInstance().Bind(kbJump, KeyHeld, m_jumpCommand.get());
    dae::InputManager::GetInstance().Bind(kbAttack, KeyDown, m_attackCommand.get());

    dae::InputManager::GetInstance().Bind(DpadLeft, m_player, KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(DpadRight, m_player, KeyHeld, m_moveRightCommand.get());

    dae::InputManager::GetInstance().Bind(A, m_player, KeyHeld, m_jumpCommand.get());
    dae::InputManager::GetInstance().Bind(X, m_player, KeyDown, m_attackCommand.get());
}

void game::PlayerInputComponent::OnDelete()
{
    dae::InputManager::GetInstance().Unbind(m_attackCommand.get());
    dae::InputManager::GetInstance().Unbind(m_jumpCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveRightCommand.get());
    dae::InputManager::GetInstance().Unbind(m_moveLeftCommand.get());
}

game::PlayerInputComponent::PlayerInputComponent(dae::GameObject &owner, int player, bool isEnemy)
    : GameComponent(owner)
      , m_player(player)
      , m_isEnemy(isEnemy)
{
}
