#ifndef MINIGIN_INCREASESCORECOMMAND_HPP
#define MINIGIN_INCREASESCORECOMMAND_HPP
#include <cstdint>

#include "ICommand.hpp"


namespace dae
{
    class GameObject;
}

namespace game
{
    class LivesScoreComponent;

    class IncreaseScoreCommand : public dae::ICommand
    {
    public:
        void Execute() override;

        IncreaseScoreCommand(dae::GameObject &object, bool isBig);

    private:
        static constexpr int SMALL_SCORE_AMOUNT{10};
        static constexpr int BIG_SCORE_AMOUNT{100};

        LivesScoreComponent* m_scoreComponent{};

        bool m_isBig{};
    };
}

#endif //MINIGIN_INCREASESCORECOMMAND_HPP