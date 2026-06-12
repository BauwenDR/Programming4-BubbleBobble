#ifndef MINIGIN_SKIPSTAGECOMMAND_H
#define MINIGIN_SKIPSTAGECOMMAND_H
#include "Event/ICommand.hpp"

class SkipStageCommand final : public dae::ICommand
{
public:
    void Execute() override;
    ~SkipStageCommand() override = default;
};

#endif //MINIGIN_SKIPSTAGECOMMAND_H
