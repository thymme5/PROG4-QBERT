#pragma once

#include "Component.h"
#include "LevelBuilder.h"
#include "QbertSoundLibrary.h"
enum class GameState {
    Playing,
    RoundComplete,
    TransitionToNextRound
};

class GameplayManagerComponent final : public dae::Component {
public:
    explicit GameplayManagerComponent(dae::GameObject& owner);
    ~GameplayManagerComponent() override = default;

    void Update() override;
    void Render() const override {}

private:
    void CheckRoundComplete();
    void StopTileFlashing();
    void StartNextRound();

    GameState m_CurrentState{};
    float m_StateTimer{};
    bool m_RoundInProgress{ true };

};
