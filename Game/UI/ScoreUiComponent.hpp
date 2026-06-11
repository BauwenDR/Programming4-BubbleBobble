#ifndef MINIGIN_SCOREUICOMPONENT_HPP
#define MINIGIN_SCOREUICOMPONENT_HPP

#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace dae
{
    class TextComponent;
}

namespace game
{
    class LivesScoreComponent;

    class ScoreUiComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override {}
        void Render() const override {}

        void OnDelete() override;

        void Notify(uint32_t event, const dae::ObserverData *data) override;

        ScoreUiComponent(dae::GameObject &owner, dae::GameObject *player);

    private:
        dae::GameObject *m_observingPlayer{};
        dae::TextComponent *m_textComponent{};
        LivesScoreComponent *m_playerLivesComponent{};
    };
}

#endif //MINIGIN_SCOREUICOMPONENT_HPP