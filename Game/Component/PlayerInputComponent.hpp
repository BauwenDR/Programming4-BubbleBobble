#ifndef MINIGIN_MOVECOMPONENT_HPP
#define MINIGIN_MOVECOMPONENT_HPP

#include <memory>

#include "Component/GameComponent.hpp"

class JumpCommand;

namespace game {
    class IncreaseScoreCommand;
    class DecreaseLivesCommand;
    class LivesScoreComponent;
    class MoveCommand;

    class PlayerInputComponent final : public dae::GameComponent
    {
    public:
        void Start() override;

        PlayerInputComponent(dae::GameObject& owner, int player);
        ~PlayerInputComponent() override;

        PlayerInputComponent(const PlayerInputComponent &other) = delete;
        PlayerInputComponent(PlayerInputComponent &&other) noexcept = delete;
        PlayerInputComponent & operator=(const PlayerInputComponent &other) = delete;
        PlayerInputComponent & operator=(PlayerInputComponent &&other) noexcept = delete;

    private:
        int player{};

        LivesScoreComponent *m_livesScoreComponent{};

        std::unique_ptr<MoveCommand> m_moveLeftCommand{};
        std::unique_ptr<MoveCommand> m_moveRightCommand{};

        std::unique_ptr<JumpCommand> m_jumpCommand{};
    };
}

#endif //MINIGIN_MOVECOMPONENT_HPP