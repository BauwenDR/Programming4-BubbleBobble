#ifndef MINIGIN_INCREASESCORECOMMAND_HPP
#define MINIGIN_INCREASESCORECOMMAND_HPP
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
        IncreaseScoreCommand(dae::GameObject &object, int scoreToAdd);
        void Execute() override;

    private:
        const int m_scoreToAdd{0};

        LivesScoreComponent* m_scoreComponent{};
    };
}

#endif //MINIGIN_INCREASESCORECOMMAND_HPP