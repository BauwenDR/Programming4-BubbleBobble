#ifndef MINIGIN_MOVECOMPONENT_HPP
#define MINIGIN_MOVECOMPONENT_HPP

#include <memory>
#include <glm/vec3.hpp>

#include "GameComponent.hpp"
#include "InputCommand.hpp"


class MoveObjectComponent final : public dae::GameComponent
{
public:
    void Start() override {}

    void Update() override;
    void Render() const override {}

    MoveObjectComponent(dae::GameObject& gameObject, bool isKeyboard, float movesSpeed);
    ~MoveObjectComponent() override = default;

private:
    glm::vec3 m_desiredDirection{};

    float m_speed{};

    std::unique_ptr<InputCommand> m_moveUpCommand{};
    std::unique_ptr<InputCommand> m_moveDownCommand{};
    std::unique_ptr<InputCommand> m_moveLeftCommand{};
    std::unique_ptr<InputCommand> m_moveRightCommand{};

    void RegisterInput(const glm::vec3 &direction);
};


#endif //MINIGIN_MOVECOMPONENT_HPP