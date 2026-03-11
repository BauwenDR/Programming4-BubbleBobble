#include "MoveObjectComponent.hpp"

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "MoveCommand.hpp"

void MoveObjectComponent::Start()
{
}

void MoveObjectComponent::Update()
{
}

MoveObjectComponent::MoveObjectComponent(dae::GameObject &gameObject, bool isKeyboard)
    : GameComponent(gameObject)
    , moveUpCommand(std::make_unique<MoveCommand>(100.0f, gameObject, glm::vec3{0.0f, -1.0f, 0.0f}))
    , moveDownCommand(std::make_unique<MoveCommand>(100.0f, gameObject, glm::vec3{0.0f, 1.0f, 0.0f}))
    , moveLeftCommand(std::make_unique<MoveCommand>(100.0f, gameObject, glm::vec3{-1.0f, 0.0f, 0.0f}))
    , moveRightCommand(std::make_unique<MoveCommand>(100.0f, gameObject, glm::vec3{1.0f, 0.0f, 0.0f}))
{
    if (isKeyboard)
    {
        dae::InputManager::Bind(SDLK_W, CommandTrigger::KeyHeld, moveUpCommand.get());
        dae::InputManager::Bind(SDLK_S, CommandTrigger::KeyHeld, moveDownCommand.get());
        dae::InputManager::Bind(SDLK_A, CommandTrigger::KeyHeld, moveLeftCommand.get());
        dae::InputManager::Bind(SDLK_D, CommandTrigger::KeyHeld, moveRightCommand.get());
    }
}
