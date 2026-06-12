#ifndef MINIGIN_MOVECOMPONENT_HPP
#define MINIGIN_MOVECOMPONENT_HPP

#include <memory>

#include "Command/JumpCommand.hpp"
#include "Command/MoveCommand.hpp"
#include "Command/SpawnBubbleCommand.hpp"
#include "Component/GameComponent.hpp"

namespace game {
    class PlayerInputComponent final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override {}

        void OnDelete() override;

        PlayerInputComponent(dae::GameObject& owner, int player, bool isEnemy);

    private:
        int m_player{};

        std::unique_ptr<MoveCommand> m_moveLeftCommand{};
        std::unique_ptr<MoveCommand> m_moveRightCommand{};

        std::unique_ptr<JumpCommand> m_jumpCommand{};
        std::unique_ptr<SpawnProjectileCommand> m_attackCommand{};

        bool m_isEnemy{};
    };
}

#endif //MINIGIN_MOVECOMPONENT_HPP