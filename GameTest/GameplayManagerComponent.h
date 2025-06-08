#pragma once
#include "Component.h"
#include "LevelBuilder.h"
#include "QbertSoundLibrary.h"

enum class GameState 
{
    Playing,
    RoundComplete,
    TransitionToNextRound
};

class GameplayManagerComponent final : public dae::Component {
public:
    explicit GameplayManagerComponent(dae::GameObject& owner);
    void Init(dae::Scene& scene, const std::string& levelPath = "../data/levels/Level01Solo.json");

    ~GameplayManagerComponent() override = default;

    void Update() override;
    void Render() const override {}

    void ForceCompleteRound();
private:
    void CheckRoundComplete();
    void StopTileFlashing();
    void StartNextRound();

    GameState m_CurrentState{};
    float m_StateTimer{};
    bool m_RoundInProgress{ true };

    dae::Scene* m_pScene = nullptr;
    std::string m_LevelPath{};
    int m_CurrentRoundIndex = 0;

};
