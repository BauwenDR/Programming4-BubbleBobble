#ifndef MINIGIN_ICOMMAND_HPP
#define MINIGIN_ICOMMAND_HPP


class ICommand
{
public:
    virtual void Execute() = 0;
    virtual ~ICommand() = default;
};


#endif //MINIGIN_ICOMMAND_HPP