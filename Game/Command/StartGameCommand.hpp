#ifndef MINIGIN_STARTGAMECOMMAND_HPP
#define MINIGIN_STARTGAMECOMMAND_HPP
#include "GameState.hpp"

#include "Event/ICommand.hpp"

namespace game
{
    class StartGameCommand final : public dae::ICommand
    {
    public:
        void Execute() override;

        explicit StartGameCommand(GameType type);
    private:
        GameType m_gameType{};
    };
}

#endif //MINIGIN_STARTGAMECOMMAND_HPP
