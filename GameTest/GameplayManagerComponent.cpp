#include "GameplayManagerComponent.h"
#include "TileComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include <fstream>

GameplayManagerComponent::GameplayManagerComponent(dae::GameObject& owner)
    : Component(owner)
{
}
void GameplayManagerComponent::Init(dae::Scene& scene, const std::string& levelPath)
{
    m_pScene = &scene;
    m_LevelPath = levelPath;
    m_CurrentRoundIndex = 1;

    LevelBuilder::LoadFromJson(scene, m_LevelPath, m_CurrentRoundIndex);
}
void GameplayManagerComponent::Update() 
{
    constexpr float deltaTime = 1.0f / 60.0f;

    switch (m_CurrentState) {
    case GameState::Playing:
        if (m_RoundInProgress)
            CheckRoundComplete();
        break;

    case GameState::RoundComplete:
        if (!QbertSoundLibrary::IsPlaying(SoundID::RoundComplete))
        {
            QbertSoundLibrary::Play(SoundID::RoundComplete);
        }

        m_StateTimer += deltaTime;

        for (auto& row : LevelBuilder::GetTileComponentMap()) 
        {
            for (auto& tile : row)
                tile->Update();
        }

        if (m_StateTimer >= 2.5f) 
        {
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
void GameplayManagerComponent::SetGameUI(dae::GameUIComponent* gameUI)
{
    m_GameUIComponent = gameUI;
}
dae::GameUIComponent* GameplayManagerComponent::GetGameUI() const
{
    return m_GameUIComponent;
}
void GameplayManagerComponent::CheckRoundComplete()
{
    bool allDone = true;

    for (const auto& row : LevelBuilder::GetTileComponentMap())
    {
        for (const auto& tile : row) 
        {
            if (!tile->IsCompleted()) 
            {
                allDone = false;
                break;
            }
        }
        if (!allDone) break;
    }

    if (allDone)
    {
        m_CurrentState = GameState::RoundComplete;
        m_StateTimer = 0.0f;
        m_RoundInProgress = false;

        for (const auto& row : LevelBuilder::GetTileComponentMap())
        {
            for (const auto& tile : row)
                tile->StartFlashing();
        }
    }
}

void GameplayManagerComponent::StopTileFlashing()
{
    for (const auto& row : LevelBuilder::GetTileComponentMap())
    {
        for (const auto& tile : row)
            tile->StopFlashing();
    }
}

void GameplayManagerComponent::StartNextRound()
{

    ++m_CurrentRoundIndex;

    //count levels
    std::ifstream file(m_LevelPath);
    if (!file.is_open())
    {
        std::cerr << "[GameplayManager] Failed to open level JSON: " << m_LevelPath << '\n';
        return;
    }

    nlohmann::json levelData;
    file >> levelData;

    int maxRounds = static_cast<int>(levelData["rounds"].size());

    if (m_CurrentRoundIndex > maxRounds)
    {
        std::cout << "[GameplayManager] All rounds completed. Level finished.\n";
        m_RoundInProgress = false;
        m_CurrentState = GameState::Playing;
        m_pOwner->NotifyObservers(dae::Event::LevelComplete);

        return;
    }

    std::cout << "[GameplayManager] Starting round " << m_CurrentRoundIndex << '\n';
    m_pOwner->NotifyObservers(dae::Event::roundComplete);

    // remove old tile gameobjects
    m_pScene->RemoveObjectsWithComponent<TileComponent>();

    // load new tiles for the next round (same level)
    LevelBuilder::LoadFromJson(*m_pScene, m_LevelPath, m_CurrentRoundIndex);

    const auto& newTileMap = LevelBuilder::GetTileMap();
    auto firstTile = newTileMap[0][0];
    auto firstTileComp = std::shared_ptr<TileComponent>(firstTile->GetComponent<TileComponent>(), [](TileComponent*) {});

    // update Qbert
    if (auto qbert = m_pQbert.lock())
    {
        auto* qbertMoveComponent = qbert->GetComponent<QbertMoveComponent>();
            
        qbertMoveComponent->SetTileMap(LevelBuilder::GetTileComponentMap());
        qbertMoveComponent->SetCurrentTile(firstTileComp);
    }

    //reset enemies (only coily for now) 
    //TODO: maybe refactor when we have more enemies
    if (auto coily = m_pCoily.lock())
    {
        auto* coilyMoveComponent = coily->GetComponent<CoilyComponent>();

        coilyMoveComponent->SetState(std::make_unique<EggState>());
        coilyMoveComponent->SetTileMap(LevelBuilder::GetTileComponentMap());
        coilyMoveComponent->SetCurrentTile(firstTileComp);
    }
    
    // set state flags
    m_CurrentState = GameState::Playing;
    m_RoundInProgress = true;
}

void GameplayManagerComponent::ForceCompleteRound()
{
    if (m_CurrentState != GameState::Playing)
        return;

    m_CurrentState = GameState::RoundComplete;
    m_StateTimer = 0.0f;
    m_RoundInProgress = false;

    for (const auto& row : LevelBuilder::GetTileComponentMap())
    {
        for (const auto& tile : row)
        {
            tile->SetState(TileState::Target);
            tile->StartFlashing();
        }
    }
}
