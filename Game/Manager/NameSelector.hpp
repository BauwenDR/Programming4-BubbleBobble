#ifndef MINIGIN_NAMESELECTOR_HPP
#define MINIGIN_NAMESELECTOR_HPP
#include <array>
#include <cstdint>
#include <memory>

#include "Component/GameComponent.hpp"

namespace dae
{
    class TextComponent;
}

namespace game
{
    class ConfirmCommand;
    class LetterChangeCommand;

    class NameSelector final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override {}
        void OnDelete() override;

        void CycleUp();
        void CycleDown();
        void NextLetter();

        explicit NameSelector(dae::GameObject &owner);
        ~NameSelector() override;

    private:
        std::unique_ptr<LetterChangeCommand> m_letterUp;
        std::unique_ptr<LetterChangeCommand> m_letterDown;
        std::unique_ptr<ConfirmCommand> m_confirm;

        std::array<int8_t, 3> m_letters{};

        dae::TextComponent *m_text{};
        int32_t m_currentLetter{};

        void SetNameText() const;
        void SwitchToLeaderboard() const;
    };
}

#endif //MINIGIN_NAMESELECTOR_HPP
