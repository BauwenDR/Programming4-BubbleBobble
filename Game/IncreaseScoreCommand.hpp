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
        IncreaseScoreCommand(dae::GameObject &object, int player, bool isBig);
        void Execute() override;

    private:
        LivesScoreComponent* m_scoreComponent{};

        uint32_t m_smallScoreEventId{};
        uint32_t m_bigScoreEventId{};

        bool m_isBig{};
    };
}

#endif //MINIGIN_INCREASESCORECOMMAND_HPP