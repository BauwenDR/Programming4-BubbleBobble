#ifndef MINIGIN_HIGHSCOREUICOMPONENT_HPP
#define MINIGIN_HIGHSCOREUICOMPONENT_HPP
#include "Component/GameComponent.hpp"
#include "Event/EventManager.hpp"

namespace dae
{
    class TextComponent;
}

namespace game
{
    class HighScoreUiComponent final : public dae::GameComponent, public dae::IEventHandler
    {
    public:
        void Start() override;
        void Update() override {}
        void OnDelete() override;

        void HandleEvent(uint32_t event) override;

        explicit HighScoreUiComponent(dae::GameObject &owner);

    private:
        dae::TextComponent *m_textComponent{};
    };
}

#endif //MINIGIN_HIGHSCOREUICOMPONENT_HPP
