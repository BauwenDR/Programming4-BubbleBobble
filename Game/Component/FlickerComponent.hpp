#ifndef MINIGIN_FLICKERCOMPONENT_HPP
#define MINIGIN_FLICKERCOMPONENT_HPP
#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace dae
{
    class TextureComponent;
}

namespace game
{
    class FlickerComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:

        void Start() override;
        void Update() override;

        void Notify(uint32_t event, dae::ObserverData const* data) override;

        explicit FlickerComponent(dae::GameObject &owner);
    private:
        constexpr static float INTERVAL{0.05f};

        dae::TextureComponent* m_texture{};

        float m_timer{};
        bool m_visible{};
        bool m_flickerEnabled{};
    };
}

#endif //MINIGIN_FLICKERCOMPONENT_HPP
