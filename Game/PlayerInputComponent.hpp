#ifndef MINIGIN_MOVECOMPONENT_HPP
#define MINIGIN_MOVECOMPONENT_HPP

#include <memory>

#include "GameComponent.hpp"
#include "IObserver.hpp"

namespace game {
    class IncreaseScoreCommand;
    class DecreaseLivesCommand;
    class LivesScoreComponent;
    class MoveCommand;

    class PlayerInputComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override {}
        void Render() const override {}

        void Notify(const dae::GameObject &object, uint32_t event, const dae::ObserverData *data) override;

        PlayerInputComponent(dae::GameObject& owner, float movesSpeed, int player);
        ~PlayerInputComponent() override;

        PlayerInputComponent(const PlayerInputComponent &other) = delete;
        PlayerInputComponent(PlayerInputComponent &&other) noexcept = delete;
        PlayerInputComponent & operator=(const PlayerInputComponent &other) = delete;
        PlayerInputComponent & operator=(PlayerInputComponent &&other) noexcept = delete;

    private:
        LivesScoreComponent *m_livesScoreComponent{};

        std::unique_ptr<MoveCommand> m_moveUpCommand{};
        std::unique_ptr<MoveCommand> m_moveDownCommand{};
        std::unique_ptr<MoveCommand> m_moveLeftCommand{};
        std::unique_ptr<MoveCommand> m_moveRightCommand{};

        std::unique_ptr<DecreaseLivesCommand> m_decreaseLivesCommand{};
        std::unique_ptr<IncreaseScoreCommand> m_increaseScoreCommandSmall{};
        std::unique_ptr<IncreaseScoreCommand> m_increaseScoreCommandBig{};
    };
}

#endif //MINIGIN_MOVECOMPONENT_HPP