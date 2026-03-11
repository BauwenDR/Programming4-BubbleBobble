#ifndef MINIGIN_ICOMMAND_HPP
#define MINIGIN_ICOMMAND_HPP

#include <functional>

// RAII Wrapper around a command function pointer
class InputCommand
{
public:
    void Execute() const;

    InputCommand(const std::function<void()> &onInput);
    ~InputCommand();

    InputCommand(const InputCommand &other) = delete;
    InputCommand(InputCommand &&other) noexcept = delete;
    InputCommand & operator=(const InputCommand &other) = delete;
    InputCommand & operator=(InputCommand &&other) noexcept = delete;

private:
    std::function<void()> m_function;
};


#endif //MINIGIN_ICOMMAND_HPP