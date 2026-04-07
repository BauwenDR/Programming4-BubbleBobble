#ifndef MINIGIN_JUMPCOMMAND_HPP
#define MINIGIN_JUMPCOMMAND_HPP
#include "ICommand.hpp"


namespace dae
{
        class GravityComponent;
}

class JumpCommand final : public dae::ICommand
{
public:
        void Execute() override;

        JumpCommand(dae::GravityComponent &gravityComponent) : m_gravityComponent(gravityComponent) {}
        ~JumpCommand() override = default;
private:
        dae::GravityComponent &m_gravityComponent;
};


#endif //MINIGIN_JUMPCOMMAND_HPP