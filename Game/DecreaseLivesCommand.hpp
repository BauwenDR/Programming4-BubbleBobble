#ifndef MINIGIN_DECREASELIVESCOMMAND_HPP
#define MINIGIN_DECREASELIVESCOMMAND_HPP

#include "ICommand.hpp"
#include "LivesScoreComponent.hpp"

namespace dae
{
    class GameObject;
}

namespace game
{
    class DecreaseLivesCommand final : public dae::ICommand
    {

    public:
        void Execute() override;

        explicit DecreaseLivesCommand(dae::GameObject &object);

    private:
        LivesScoreComponent *m_livesComponent{};
    };
}

#endif //MINIGIN_DECREASELIVESCOMMAND_HPP