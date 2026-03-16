#ifndef MINIGIN_MOVECOMPONENT_HPP
#define MINIGIN_MOVECOMPONENT_HPP

#include <memory>
#include <glm/vec3.hpp>

#include "EventManager.hpp"
#include "GameComponent.hpp"
#include "InputCommand.hpp"
#include "IObserver.hpp"

namespace game {
    class MoveObjectComponent final : public dae::GameComponent, public dae::IObserver, public dae::IEventHandler
    {
    public:
        void Start() override {}

        void Update() override;
        void Render() const override {}

        void Notify(dae::GameObject &object, uint32_t event) override;
        void HandleEvent(uint32_t event) override;

        MoveObjectComponent(dae::GameObject& gameObject, float movesSpeed, int controller);
        ~MoveObjectComponent() override = default;

    private:
        glm::vec3 m_desiredDirection{};

        float m_speed{};

        std::unique_ptr<InputCommand> m_moveUpCommand{};
        std::unique_ptr<InputCommand> m_moveDownCommand{};
        std::unique_ptr<InputCommand> m_moveLeftCommand{};
        std::unique_ptr<InputCommand> m_moveRightCommand{};

        std::unique_ptr<InputCommand> m_dieCommand{};
        std::unique_ptr<InputCommand> m_bigEventCommand{};
        std::unique_ptr<InputCommand> m_smallEventCommand{};

        void RegisterInput(const glm::vec3 &direction);
    };
}


#endif //MINIGIN_MOVECOMPONENT_HPP