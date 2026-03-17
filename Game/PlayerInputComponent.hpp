#ifndef MINIGIN_MOVECOMPONENT_HPP
#define MINIGIN_MOVECOMPONENT_HPP

#include <memory>

#include "GameComponent.hpp"

namespace game {
    class MoveCommand;

    class PlayerInputComponent final : public dae::GameComponent
    {
    public:
        void Start() override {}
        void Update() override {}
        void Render() const override {}

        PlayerInputComponent(dae::GameObject& owner, float movesSpeed, int player);
        ~PlayerInputComponent() override;

        PlayerInputComponent(const PlayerInputComponent &other) = delete;
        PlayerInputComponent(PlayerInputComponent &&other) noexcept = delete;
        PlayerInputComponent & operator=(const PlayerInputComponent &other) = delete;
        PlayerInputComponent & operator=(PlayerInputComponent &&other) noexcept = delete;

    private:
        std::unique_ptr<MoveCommand> m_moveUpCommand{};
        std::unique_ptr<MoveCommand> m_moveDownCommand{};
        std::unique_ptr<MoveCommand> m_moveLeftCommand{};
        std::unique_ptr<MoveCommand> m_moveRightCommand{};
    };
}

#endif //MINIGIN_MOVECOMPONENT_HPP