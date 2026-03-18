#ifndef MINIGIN_SCOREUICOMPONENT_HPP
#define MINIGIN_SCOREUICOMPONENT_HPP

#include "EventManager.hpp"
#include "GameComponent.hpp"
#include "IObserver.hpp"

namespace dae
{
    class TextComponent;
}

namespace game
{
    class LivesScoreComponent;

    // Having this be an observer would probably be a better idea
    // I have chosen to go for an Event Handler as of Assignment requirements
    class ScoreUiComponent final : public dae::GameComponent, public dae::IEventHandler
    {
    public:
        // GameComponent functions
        void Start() override;
        void Update() override {}
        void Render() const override {}

        // Observer
        void HandleEvent(uint32_t event) override;

        // We should prob get player from some global object instead of param
        // But for now we use a param anyway
        explicit ScoreUiComponent(dae::GameObject &owner, dae::GameObject &player);
        ~ScoreUiComponent() override;

        ScoreUiComponent(const ScoreUiComponent &other) = delete;
        ScoreUiComponent(ScoreUiComponent &&other) noexcept = delete;
        ScoreUiComponent & operator=(const ScoreUiComponent &other) = delete;
        ScoreUiComponent & operator=(ScoreUiComponent &&other) noexcept = delete;
    private:
        dae::GameObject &m_observingPlayer;
        dae::TextComponent *m_textComponent{nullptr};
        LivesScoreComponent *m_playerLivesComponent{nullptr};
    };
}

#endif //MINIGIN_SCOREUICOMPONENT_HPP