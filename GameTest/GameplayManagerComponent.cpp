#include "GameplayManagerComponent.h"
#include "TileComponent.h"
#include "GameObject.h"
#include "Scene.h"

GameplayManagerComponent::GameplayManagerComponent(dae::GameObject& owner)
    : Component(owner)
{
}

void GameplayManagerComponent::Update() {
    constexpr float deltaTime = 1.0f / 60.0f;

    switch (m_CurrentState) {
    case GameState::Playing:
        if (m_RoundInProgress)
            CheckRoundComplete();
        break;

    case GameState::RoundComplete:
        m_StateTimer += deltaTime;

        for (auto& row : LevelBuilder::GetTileComponentMap()) {
            for (auto& tile : row)
                tile->Update();
        }

        if (m_StateTimer >= 2.0f) {
            StopTileFlashing();
            StartNextRound();
            m_CurrentState = GameState::Playing;
            m_StateTimer = 0.0f;
            m_RoundInProgress = true;
        }
        break;

    case GameState::TransitionToNextRound:
        break;
    }
}

void GameplayManagerComponent::CheckRoundComplete() {
    bool allDone = true;

    for (const auto& row : LevelBuilder::GetTileComponentMap()) {
        for (const auto& tile : row) {
            if (!tile->IsCompleted()) {
                allDone = false;
                break;
            }
        }
        if (!allDone) break;
    }

    if (allDone) {
        m_CurrentState = GameState::RoundComplete;
        m_StateTimer = 0.0f;
        m_RoundInProgress = false;
        QbertSoundLibrary::Play(SoundID::RoundComplete);
        for (const auto& row : LevelBuilder::GetTileComponentMap()) {
            for (const auto& tile : row)
                tile->StartFlashing();
        }
    }
}

void GameplayManagerComponent::StopTileFlashing() {
    for (const auto& row : LevelBuilder::GetTileComponentMap()) {
        for (const auto& tile : row)
            tile->StopFlashing();
    }
}

void GameplayManagerComponent::StartNextRound()
{

}
