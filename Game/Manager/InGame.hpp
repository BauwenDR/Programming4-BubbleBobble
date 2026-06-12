#ifndef MINIGIN_INGAME_H
#define MINIGIN_INGAME_H
#include "Command/MuteCommand.hpp"
#include "Command/SkipStageCommand.hpp"
#include "Component/GameComponent.hpp"
#include "Event/EventManager.hpp"

namespace game
{
    class InGame final : public dae::GameComponent, public dae::IEventHandler
    {
    public:
        void Start() override;
        void Update() override {}
        void OnDelete() override;

        void HandleEvent(uint32_t event) override;

        explicit InGame(dae::GameObject &owner);

    private:
        SkipStageCommand m_skipStage{};
        MuteCommand m_mute{};

        void HandleLiveChanged() const;
        void HandleScoreChange() const;
    };
}

#endif //MINIGIN_INGAME_H
