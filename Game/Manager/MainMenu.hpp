#ifndef MINIGIN_MAINMENU_HPP
#define MINIGIN_MAINMENU_HPP
#include "Command/StartGameCommand.hpp"
#include "Component/GameComponent.hpp"

namespace game
{
    class MainMenu final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override {}
        void OnDelete() override;

        explicit MainMenu(dae::GameObject &owner);

    private:
        StartGameCommand m_startSingleGameCommand;
        StartGameCommand m_startCoopGameCommand;
        StartGameCommand m_startVersusGameCommand;
    };
}

#endif //MINIGIN_MAINMENU_HPP
