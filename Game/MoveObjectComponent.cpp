#include "MoveObjectComponent.hpp"

#include <iostream>
#include <ostream>

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Sdbm.hpp"
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

void game::MoveObjectComponent::Notify(dae::GameObject&, uint32_t event) {
    if (event != dae::sdbm_hash("PLAYER_DEATH")) return;

    std::cout << "Event observed" << std::endl;
}

void game::MoveObjectComponent::HandleEvent(uint32_t event) {
    switch (event) {
        case dae::sdbm_hash("BIG_EVENT"):
            std::cout << "Big event received" << std::endl;
            break;
        case dae::sdbm_hash("SMALL_EVENT"):
            std::cout << "Small event received" << std::endl;
            break;
        default:
            break;
    }
}

game::MoveObjectComponent::MoveObjectComponent(dae::GameObject &gameObject, float moveSpeed, int controller)
    : GameComponent(gameObject)
    , m_speed{moveSpeed}
    , m_moveUpCommand(std::make_unique<InputCommand>([this] {RegisterInput({0.0f, -1.0f, 0.0f});}))
    , m_moveDownCommand(std::make_unique<InputCommand>([this] {RegisterInput({0.0f, 1.0f, 0.0f});}))
    , m_moveLeftCommand(std::make_unique<InputCommand>([this] {RegisterInput({-1.0f, 0.0f, 0.0f});}))
    , m_moveRightCommand(std::make_unique<InputCommand>([this] {RegisterInput({1.0f, 0.0f, 0.0f});}))
    , m_dieCommand(std::make_unique<InputCommand>([&gameObject] {gameObject.NotifyObservers(dae::sdbm_hash("PLAYER_DEATH"));}))
    , m_bigEventCommand(std::make_unique<InputCommand>([] {dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("BIG_EVENT"));}))
    , m_smallEventCommand(std::make_unique<InputCommand>([] {dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("SMALL_EVENT"));}))
{
    gameObject.AddObserver(this);
    dae::EventManager::GetInstance().AttachHandler(dae::sdbm_hash("BIG_EVENT"), this);
    dae::EventManager::GetInstance().AttachHandler(dae::sdbm_hash("SMALL_EVENT"), this);

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

    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::X, controller, dae::Input::CommandTrigger::KeyDown, m_dieCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::A, controller, dae::Input::CommandTrigger::KeyDown, m_bigEventCommand.get());
    dae::InputManager::GetInstance().Bind(dae::Input::ControllerKey::B, controller, dae::Input::CommandTrigger::KeyDown, m_smallEventCommand.get());
}

void game::MoveObjectComponent::RegisterInput(const glm::vec3 &direction)
{
    m_desiredDirection += direction;
}
