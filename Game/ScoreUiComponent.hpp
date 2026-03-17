#ifndef MINIGIN_SCOREUICOMPONENT_HPP
#define MINIGIN_SCOREUICOMPONENT_HPP

#include "EventManager.hpp"
#include "GameComponent.hpp"
#include "IObserver.hpp"


namespace game
{
    class ScoreUiComponent : public dae::GameComponent, dae::IObserver
    {
    public:
        void Start() override;
        void Update() override;
        void Render() const override {}

        void Notify(dae::GameObject &object, uint32_t event) override;

        explicit ScoreUiComponent(dae::GameObject &owner);
        ~ScoreUiComponent() override;

        ScoreUiComponent(const ScoreUiComponent &other) = delete;
        ScoreUiComponent(ScoreUiComponent &&other) noexcept = delete;
        ScoreUiComponent & operator=(const ScoreUiComponent &other) = delete;
        ScoreUiComponent & operator=(ScoreUiComponent &&other) noexcept = delete;
    };
}

#endif //MINIGIN_SCOREUICOMPONENT_HPP