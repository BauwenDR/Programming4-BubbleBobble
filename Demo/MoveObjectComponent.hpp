#ifndef MINIGIN_MOVECOMPONENT_HPP
#define MINIGIN_MOVECOMPONENT_HPP

#include <memory>

#include "GameComponent.hpp"
#include "ICommand.hpp"


class MoveObjectComponent final : public dae::GameComponent
{
public:
    void Start() override;

    void Update() override;
    void Render() const override {}

    MoveObjectComponent(dae::GameObject& gameObject, bool isKeyboard);
    ~MoveObjectComponent() override = default;

private:
    std::unique_ptr<ICommand> moveUpCommand;
    std::unique_ptr<ICommand> moveDownCommand;
    std::unique_ptr<ICommand> moveLeftCommand;
    std::unique_ptr<ICommand> moveRightCommand;
};


#endif //MINIGIN_MOVECOMPONENT_HPP