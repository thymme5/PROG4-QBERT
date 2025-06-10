#pragma once
#include <memory>
#include <iostream>
#include "Scene.h"
#include "GameplayManagerComponent.h"
#include "GameModeManager.h"

class QbertSceneBuilder
{
public:
    static std::shared_ptr<dae::GameObject> CreateQbertPlayer(const std::shared_ptr<TileComponent>& startTile, const std::shared_ptr<dae::Font>& font, bool isSecondPlayer);
    //static dae::Scene& CreateQbertScene(const std::string& levelPath, GameModeType mode, std::shared_ptr<GameplayManagerComponent>& outManager);
	//static void BuildQbertScene(dae::Scene& scene, const std::string& levelPath, GameModeType mode, std::shared_ptr<GameplayManagerComponent>& outManager);
    static void BuildQbertScene(dae::Scene& scene, const std::string& levelPath, GameModeType mode);



};
