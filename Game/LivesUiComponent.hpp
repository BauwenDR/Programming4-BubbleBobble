#ifndef MINIGIN_LIVESUICOMPONENT_HPP
#define MINIGIN_LIVESUICOMPONENT_HPP
#include <cstdint>

#include "GameComponent.hpp"
#include "IObserver.hpp"

namespace dae
{
    class TextComponent;
}

namespace game
{
    class LivesScoreComponent;

    class LivesUiComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        // GameComponent functions
        void Start() override;
        void Update() override {}
        void Render() const override {}

        // Observer
        void Notify(dae::GameObject &object, uint32_t event) override;

        // We should prob get player from some global object instead of param
        // But for now we use a param anyway
        explicit LivesUiComponent(dae::GameObject &owner, dae::GameObject &player);
        ~LivesUiComponent() override;

        LivesUiComponent(const LivesUiComponent &other) = delete;
        LivesUiComponent(LivesUiComponent &&other) noexcept = delete;
        LivesUiComponent & operator=(const LivesUiComponent &other) = delete;
        LivesUiComponent & operator=(LivesUiComponent &&other) noexcept = delete;

    private:
        dae::GameObject &m_observingPlayer;
        dae::TextComponent *m_textComponent{nullptr};
        LivesScoreComponent *m_playerLivesComponent{nullptr};
    };
}

#endif //MINIGIN_LIVESUICOMPONENT_HPP