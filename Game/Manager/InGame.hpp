#ifndef MINIGIN_INGAME_H
#define MINIGIN_INGAME_H
#include "Command/MuteCommand.hpp"
#include "Command/SkipStageCommand.hpp"
#include "Component/GameComponent.hpp"

class InGame final : public dae::GameComponent
{
public:
    void Start() override;
    void Update() override {}
    void OnDelete() override;

    explicit InGame(dae::GameObject &owner);

private:
    SkipStageCommand m_skipStage{};
    MuteCommand m_mute{};
};

#endif //MINIGIN_INGAME_H
