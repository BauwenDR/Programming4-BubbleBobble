#ifndef MINIGIN_LIVESUICOMPONENT_HPP
#define MINIGIN_LIVESUICOMPONENT_HPP
#include <cstdint>

#include "GameComponent.hpp"
#include "IObserver.hpp"

namespace game
{
    class LivesUiComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        // GameComponent functions
        void Start() override;
        void Update() override;
        void Render() const override {}

        // Observer
        void Notify(dae::GameObject &object, uint32_t event) override;

        explicit LivesUiComponent(dae::GameObject &owner);
        ~LivesUiComponent() override;

        LivesUiComponent(const LivesUiComponent &other) = delete;
        LivesUiComponent(LivesUiComponent &&other) noexcept = delete;
        LivesUiComponent & operator=(const LivesUiComponent &other) = delete;
        LivesUiComponent & operator=(LivesUiComponent &&other) noexcept = delete;
    };
}

#endif //MINIGIN_LIVESUICOMPONENT_HPP