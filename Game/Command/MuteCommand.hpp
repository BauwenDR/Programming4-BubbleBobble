#ifndef MINIGIN_MUTECOMMAND_H
#define MINIGIN_MUTECOMMAND_H
#include "Event/ICommand.hpp"

class MuteCommand final : public dae::ICommand
{
public:
    void Execute() override;
    ~MuteCommand() override = default;
};

#endif //MINIGIN_MUTECOMMAND_H
