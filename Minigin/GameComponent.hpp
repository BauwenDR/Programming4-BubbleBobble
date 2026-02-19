#ifndef MINIGIN_GAMECOMPONENT_HPP
#define MINIGIN_GAMECOMPONENT_HPP


namespace dae
{
    class GameObject;

    class GameComponent
    {
    public:

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void Render() const = 0;

        [[nodiscard]] GameObject *GetGameObject() const;
        [[nodiscard]] bool IsMarkedForDelete() const;

        virtual ~GameComponent() = default;

        GameComponent(const GameComponent &other) = delete;
        GameComponent(GameComponent &&other) noexcept = delete;
        GameComponent &operator=(const GameComponent &other) = delete;
        GameComponent &operator=(GameComponent &&other) noexcept = delete;

    protected:
        explicit GameComponent(GameObject* owner);

    private:
        GameObject* m_pGameObject{};
        bool m_markedForDeletion{false};
    };
}


#endif //MINIGIN_GAMECOMPONENT_HPP
