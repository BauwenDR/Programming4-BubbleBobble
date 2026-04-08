#ifndef MINIGIN_ICOMMAND_HPP
#define MINIGIN_ICOMMAND_HPP

namespace dae
{
    class ICommand
    {
    public:
        virtual void Execute() = 0;

        ICommand() = default;
        virtual ~ICommand() = default;

        ICommand(const ICommand &other) = delete;
        ICommand(ICommand &&other) noexcept = delete;
        ICommand & operator=(const ICommand &other) = delete;
        ICommand & operator=(ICommand &&other) noexcept = delete;
    };
}

#endif //MINIGIN_ICOMMAND_HPP