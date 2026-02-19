#ifndef MINIGIN_FPSCOMPONENT_HPP
#define MINIGIN_FPSCOMPONENT_HPP

#include "GameComponent.hpp"


namespace dae
{
    class TextComponent;
}

namespace demo
{
    class FpsComponent : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override;
        void Render() const override {};

        explicit FpsComponent(dae::GameObject *pGameObject) : GameComponent(pGameObject) {}
        ~FpsComponent() override = default;

        FpsComponent(const FpsComponent &other) = delete;
        FpsComponent(FpsComponent &&other) noexcept = delete;
        FpsComponent &operator=(const FpsComponent &other) = delete;
        FpsComponent &operator=(FpsComponent &&other) noexcept = delete;

    private:
        dae::TextComponent *m_textComponent{};

        constexpr static float RefreshThreshold{0.5f};
        float m_elapsedTime{};
        int m_passedFrames{};
    };
}
#endif //MINIGIN_FPSCOMPONENT_HPP
