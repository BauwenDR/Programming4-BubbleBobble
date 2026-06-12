#ifndef MINIGIN_GAMEOVER_HPP
#define MINIGIN_GAMEOVER_HPP
#include "Command/MainMenuCommand.hpp"
#include "Component/GameComponent.hpp"

namespace game
{
    class GameOver final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override;
        void OnDelete() override;

        GameOver(dae::GameObject &owner);
    private:
        MainMenuCommand m_mainMenu{};
    };
}

#endif //MINIGIN_GAMEOVER_HPP
