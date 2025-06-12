#pragma once
#include <memory>
#include <iostream>
#include "Scene.h"
#include "GameplayManagerComponent.h"
#include "GameModeManager.h"

class QbertSceneBuilder
{
public:
    static void BuildMainMenu(dae::Scene& scene, const std::shared_ptr<dae::Font>& font);
    static void BuildQbertScene(dae::Scene& scene, const std::string& levelPath);
    static std::shared_ptr<dae::GameObject> CreateQbertPlayer(const std::shared_ptr<TileComponent>& startTile, const std::shared_ptr<dae::Font>& font, bool isSecondPlayer);
    static std::shared_ptr<dae::GameObject> SpawnCoily(const std::shared_ptr<TileComponent>& startTile, const std::shared_ptr<dae::GameObject>& qbert, bool isPlayerControlled);

    //different gamemodes
    static void BuildSinglePlayerScene(dae::Scene& scene, const std::string& levelPath);
    static void BuildCoopScene(dae::Scene& scene, const std::string& levelPath);
    static void BuildVersusScene(dae::Scene& scene, const std::string& levelPath);
};
