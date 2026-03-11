#include "MoveObjectComponent.hpp"

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Time.hpp"

void MoveObjectComponent::Update()
{
   auto &gameObject{GetGameObject()};

    if (m_desiredDirection != glm::vec3(0))
    {
        m_desiredDirection = normalize(m_desiredDirection);
        gameObject.SetLocalPosition(gameObject.GetLocalTransform().GetPosition() + m_desiredDirection * m_speed * Time::timeDelta());
    }

    m_desiredDirection = {0.0f, 0.0f, 0.0f};
}

MoveObjectComponent::MoveObjectComponent(dae::GameObject &gameObject, bool isKeyboard, float moveSpeed)
    : GameComponent(gameObject)
    , m_speed{moveSpeed}
    , m_moveUpCommand(std::make_unique<InputCommand>([this] {RegisterInput({0.0f, -1.0f, 0.0f});}))
    , m_moveDownCommand(std::make_unique<InputCommand>([this] {RegisterInput({0.0f, 1.0f, 0.0f});}))
    , m_moveLeftCommand(std::make_unique<InputCommand>([this] {RegisterInput({-1.0f, 0.0f, 0.0f});}))
    , m_moveRightCommand(std::make_unique<InputCommand>([this] {RegisterInput({1.0f, 0.0f, 0.0f});}))
{
    if (isKeyboard)
    {
        dae::InputManager::Bind(SDLK_W, dae::InputManager::CommandTrigger::KeyHeld, m_moveUpCommand.get());
        dae::InputManager::Bind(SDLK_S, dae::InputManager::CommandTrigger::KeyHeld, m_moveDownCommand.get());
        dae::InputManager::Bind(SDLK_A, dae::InputManager::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
        dae::InputManager::Bind(SDLK_D, dae::InputManager::CommandTrigger::KeyHeld, m_moveRightCommand.get());
    } else
    {
        dae::InputManager::Bind(dae::InputManager::ControllerKey::DpadUp, dae::InputManager::CommandTrigger::KeyHeld, m_moveUpCommand.get());
        dae::InputManager::Bind(dae::InputManager::ControllerKey::DpadDown, dae::InputManager::CommandTrigger::KeyHeld, m_moveDownCommand.get());
        dae::InputManager::Bind(dae::InputManager::ControllerKey::DpadLeft, dae::InputManager::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
        dae::InputManager::Bind(dae::InputManager::ControllerKey::DpadRight, dae::InputManager::CommandTrigger::KeyHeld, m_moveRightCommand.get());
    }
}

void MoveObjectComponent::RegisterInput(const glm::vec3 &direction)
{
    m_desiredDirection += direction;
}
