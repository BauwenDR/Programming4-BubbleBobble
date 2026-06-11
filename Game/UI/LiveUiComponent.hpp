#ifndef MINIGIN_LIVEUICOMPONENT_HPP
#define MINIGIN_LIVEUICOMPONENT_HPP
#include <vector>

#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace game
{
    class LivesScoreComponent;

    class LiveUiComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override {}

        void OnDelete() override;

        void Notify(uint32_t event, dae::ObserverData const *data) override;

        LiveUiComponent(dae::GameObject &owner, dae::GameObject *player, bool leftToRight);

    private:
        constexpr static float PER_ITEM_OFFSET{8.0f * 4.0f};

        std::vector<GameComponent*> m_healthComponents{};

        dae::GameObject *m_observingPlayer{};
        LivesScoreComponent *m_playerLivesComponent{};

        bool m_leftToRight{};

        void ResizeLiveComponents(size_t lives);
    };
}

#endif //MINIGIN_LIVEUICOMPONENT_HPP