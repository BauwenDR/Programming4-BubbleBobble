#ifndef MINIGIN_GAMECOMPONENT_HPP
#define MINIGIN_GAMECOMPONENT_HPP

namespace dae
{
    class GameObject;

    class GameComponent
    {
    public:

        virtual void Start() {}
        virtual void Update() {}
        virtual void LateUpdate() {}
        virtual void Render() const {}

        void MarkForDelete();

        [[nodiscard]] GameObject &GetGameObject() const;
        [[nodiscard]] bool IsMarkedForDelete() const;

        GameComponent() = delete;
        virtual ~GameComponent() = default;

        GameComponent(const GameComponent &other) = delete;
        GameComponent(GameComponent &&other) noexcept = delete;
        GameComponent &operator=(const GameComponent &other) = delete;
        GameComponent &operator=(GameComponent &&other) noexcept = delete;

    protected:
        explicit GameComponent(GameObject &owner) : m_GameObject(owner) {}

    private:
        GameObject &m_GameObject;
        bool m_markedForDeletion{false};
    };
}

#endif //MINIGIN_GAMECOMPONENT_HPP
