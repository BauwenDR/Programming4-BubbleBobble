#include "MoveObjectComponent.hpp"

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Time.hpp"

void game::MoveObjectComponent::Update()
{
   auto &gameObject{GetGameObject()};

    if (m_desiredDirection != glm::vec3(0))
    {
        m_desiredDirection = normalize(m_desiredDirection);
        gameObject.SetLocalPosition(gameObject.GetLocalTransform().GetPosition() + m_desiredDirection * m_speed * Time::timeDelta());
    }

    m_desiredDirection = {0.0f, 0.0f, 0.0f};
}

game::MoveObjectComponent::MoveObjectComponent(dae::GameObject &gameObject, float moveSpeed, int controller)
    : GameComponent(gameObject)
    , m_speed{moveSpeed}
    , m_moveUpCommand(std::make_unique<InputCommand>([this] {RegisterInput({0.0f, -1.0f, 0.0f});}))
    , m_moveDownCommand(std::make_unique<InputCommand>([this] {RegisterInput({0.0f, 1.0f, 0.0f});}))
    , m_moveLeftCommand(std::make_unique<InputCommand>([this] {RegisterInput({-1.0f, 0.0f, 0.0f});}))
    , m_moveRightCommand(std::make_unique<InputCommand>([this] {RegisterInput({1.0f, 0.0f, 0.0f});}))
{
    if (controller == 0)
    {
        dae::InputManager::GetInstance().Bind(SDLK_W, dae::Input::CommandTrigger::KeyHeld, m_moveUpCommand.get());
        dae::InputManager::GetInstance().Bind(SDLK_S, dae::Input::CommandTrigger::KeyHeld, m_moveDownCommand.get());
        dae::InputManager::GetInstance().Bind(SDLK_A, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
        dae::InputManager::GetInstance().Bind(SDLK_D, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());
    } else {
        dae::InputManager::GetInstance().Bind(SDLK_UP, dae::Input::CommandTrigger::KeyHeld, m_moveUpCommand.get());
        dae::InputManager::GetInstance().Bind(SDLK_DOWN, dae::Input::CommandTrigger::KeyHeld, m_moveDownCommand.get());
        dae::InputManager::GetInstance().Bind(SDLK_LEFT, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
        dae::InputManager::GetInstance().Bind(SDLK_RIGHT, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());
    }

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadUp, controller, dae::Input::CommandTrigger::KeyHeld, m_moveUpCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadDown, controller, dae::Input::CommandTrigger::KeyHeld, m_moveDownCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadLeft, controller, dae::Input::CommandTrigger::KeyHeld, m_moveLeftCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::DpadRight, controller, dae::Input::CommandTrigger::KeyHeld, m_moveRightCommand.get());
}

void game::MoveObjectComponent::RegisterInput(const glm::vec3 &direction)
{
    m_desiredDirection += direction;
}
