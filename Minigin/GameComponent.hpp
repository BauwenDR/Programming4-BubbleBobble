#ifndef MINIGIN_GAMECOMPONENT_HPP
#define MINIGIN_GAMECOMPONENT_HPP


namespace dae
{
    class GameObject;
}

class GameComponent
{
public:
    virtual void start([[maybe_unused]] dae::GameObject &object) = 0;
    virtual void update([[maybe_unused]] dae::GameObject &object) = 0;
    virtual void render([[maybe_unused]] const dae::GameObject &object) const = 0;

    GameComponent() = default;
    virtual ~GameComponent() = 0;

    GameComponent(const GameComponent &other) = delete;
    GameComponent(GameComponent &&other) noexcept = delete;
    GameComponent &operator=(const GameComponent &other) = delete;
    GameComponent &operator=(GameComponent &&other) noexcept = delete;
};


#endif //MINIGIN_GAMECOMPONENT_HPP
