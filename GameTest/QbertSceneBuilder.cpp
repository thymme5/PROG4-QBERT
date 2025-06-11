#include "QbertSceneBuilder.h"

#include <memory>
#include <iostream>

#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SoundService.h"

#include "GameplayManagerComponent.h"
#include "QbertMoveComponent.h"
#include "CoilyComponent.h"
#include "EggState.h"
#include "TileComponent.h"
#include "LevelBuilder.h"
#include "GameUIComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPScounterComponent.h"
#include "ToggleMuteCommand.h"
#include "MoveCommand.h"
#include "FinishRoundCommand.h"
#include "QbertSoundLibrary.h"
#include "GameModeManager.h"
#include "MainMenuUIComponent.h"
#include "MoveMenuArrow.h"
#include "EnterGameMode.h"
#include "InputBindingHelper.h"


std::shared_ptr<dae::GameObject> QbertSceneBuilder::CreateQbertPlayer(const std::shared_ptr<TileComponent>& startTile, const std::shared_ptr<dae::Font>& font, bool isSecondPlayer)
{
	font;

	auto qbert = std::make_shared<dae::GameObject>();
	qbert->AddComponent<dae::TextureComponent>(*qbert, isSecondPlayer ? "Qbert P2 Spritesheet.png" : "Qbert P1 Spritesheet.png", 2.f, 4);
	auto* moveComp = qbert->AddComponent<QbertMoveComponent>(*qbert);
	moveComp->SetTileMap(LevelBuilder::GetTileComponentMap());
	moveComp->SetCurrentTile(startTile);
	return qbert;
}

void QbertSceneBuilder::BuildMainMenu(dae::Scene& scene, const std::shared_ptr<dae::Font>& font)
{
    // === main menu component ===
    auto go = std::make_shared<dae::GameObject>();
    auto UIcomponent = go->AddComponent<MainMenuUIComponent>(*go);

    scene.Add(go);

    // === options ===
    const float baseX = 200.0f;
    const float baseY = 350.0f;
    const float spacing = 50.0f;

    std::vector<std::string> options = { "Solo mode", "Co-op Mode", "Versus mode" };
    for (size_t i = 0; i < options.size(); ++i)
    {
        auto optionGO = std::make_shared<dae::GameObject>();
        optionGO->AddComponent<dae::TextComponent>(*optionGO, options[i], font);
        optionGO->SetPosition(baseX, baseY + i * spacing);
        scene.Add(optionGO);
    }

    // === Selection Arrow ===
    auto arrowGO = std::make_shared<dae::GameObject>();
    arrowGO->AddComponent<dae::TextureComponent>(*arrowGO, "Selection Arrow.png", 2.f);
    arrowGO->SetPosition(180.f, 355.f);
    UIcomponent->SetArrow(arrowGO);
    scene.Add(arrowGO);

    // === main menu input bindings ===
    //TODO: controller input
    auto& inputManager = dae::InputManager::GetInstance();

    auto moveArrowUp = std::make_shared<MoveMenuArrow>(UIcomponent, -1.f);
    inputManager.BindCommand(SDLK_UP, KeyState::Down, moveArrowUp);

    auto moveArrowDown = std::make_shared<MoveMenuArrow>(UIcomponent, 1.f);
    inputManager.BindCommand(SDLK_DOWN, KeyState::Down, moveArrowDown);

    // === Confirm selection command ===
    auto confirmCommand = std::make_shared<EnterGameMode>(UIcomponent);
    inputManager.BindCommand(SDLK_RETURN, KeyState::Down, confirmCommand);
}

void QbertSceneBuilder::BuildQbertScene(dae::Scene& scene, const std::string& levelPath)
{
    auto& inputManager = dae::InputManager::GetInstance();
    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

    // === Gameplay Manager ===
    auto controller = std::make_shared<dae::GameObject>();
    auto* manager = controller->AddComponent<GameplayManagerComponent>(*controller);
    manager->Init(scene, levelPath);
    scene.Add(controller);

    // === FPS counter ===
    auto fpsGO = std::make_shared<dae::GameObject>();
    fpsGO->AddComponent<dae::TextComponent>(*fpsGO, "0 FPS", font);
    fpsGO->AddComponent<dae::FPScounterComponent>(*fpsGO);
    scene.Add(fpsGO);

    // === Game UI ===
    auto uiGO = std::make_shared<dae::GameObject>();
    auto* gameUI = uiGO->AddComponent<dae::GameUIComponent>(*uiGO);
    uiGO->AddComponent<dae::TextComponent>(*uiGO, " ", dae::ResourceManager::GetInstance().LoadFont("minecraft.ttf", 18));
    uiGO->SetPosition(5, 50);
    scene.Add(uiGO);

    manager->SetGameUI(gameUI); // Store reference to UI in manager
    controller->AddObserver(gameUI);

    // === Round & Level UI ===
    auto roundGO = std::make_shared<dae::GameObject>();
    roundGO->AddComponent<dae::TextComponent>(*roundGO, "ROUND: 1", font);
    roundGO->SetPosition(400, 80);
    scene.Add(roundGO);

    auto levelGO = std::make_shared<dae::GameObject>();
    levelGO->AddComponent<dae::TextComponent>(*levelGO, "LEVEL: 1", font);
    levelGO->SetPosition(400, 110);
    scene.Add(levelGO);

    gameUI->SetRoundText(std::shared_ptr<dae::TextComponent>(roundGO->GetComponent<dae::TextComponent>(), [](dae::TextComponent*) {}));
    gameUI->SetLevelText(std::shared_ptr<dae::TextComponent>(levelGO->GetComponent<dae::TextComponent>(), [](dae::TextComponent*) {}));

    // === Mute toggle ===
    auto toggleMute = std::make_shared<ToggleMuteCommand>();
    inputManager.BindCommand(SDLK_F2, KeyState::Down, toggleMute);

    auto soundService = dae::ServiceLocator::GetSoundService();
    if (soundService)
    {
        soundService->SetVolume(10);
        QbertSoundLibrary::LoadAllSounds();
    }
}
void QbertSceneBuilder::BuildSinglePlayerScene(dae::Scene& scene, const std::string& levelPath)
{
    BuildQbertScene(scene, levelPath);

    // === create qbert ===
    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto tileMap = LevelBuilder::GetTileMap();
    auto tileGO = tileMap[0][0];
    auto tileComp = std::shared_ptr<TileComponent>(tileGO->GetComponent<TileComponent>(), [](TileComponent*) {});

    auto qbert = CreateQbertPlayer(tileComp, font, false);
    scene.Add(qbert);

    // === Connect Qbert to gameplayManager & UI ===
    if (auto managerGO = scene.FindFirstObjectOfType<GameplayManagerComponent>())
    {
        auto* manager = managerGO->GetComponent<GameplayManagerComponent>();
        manager->SetQbert(qbert);
        if (auto* gameUI = manager->GetGameUI())
        {
            qbert->AddObserver(gameUI);
        }
    }

    // === Input binding ===
    InputBindingHelper::BindPlayer1GamepadInputs(qbert.get());
    InputBindingHelper::BindPlayer1KeyboardInputs(qbert.get());
}

void QbertSceneBuilder::BuildCoopScene(dae::Scene& scene, const std::string& levelPath)
{
    BuildQbertScene(scene, levelPath);

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto tileMap = LevelBuilder::GetTileMap();

    // P1 starts top-left
    auto p1TileGO = tileMap[0][0];
    auto p1Tile = std::shared_ptr<TileComponent>(p1TileGO->GetComponent<TileComponent>(), [](TileComponent*) {});
    auto qbert1 = CreateQbertPlayer(p1Tile, font, false);
    scene.Add(qbert1);

    // P2 starts bottom-right
    int rows = static_cast<int>(tileMap.size());
    int cols = static_cast<int>(tileMap.back().size());
    auto p2TileGO = tileMap[rows - 1][cols - 1];
    auto p2Tile = std::shared_ptr<TileComponent>(p2TileGO->GetComponent<TileComponent>(), [](TileComponent*) {});
    auto qbert2 = CreateQbertPlayer(p2Tile, font, true);
    scene.Add(qbert2);

    // === Connect them to gameplay ===
    if (auto managerGO = scene.FindFirstObjectOfType<GameplayManagerComponent>())
    {
        auto* manager = managerGO->GetComponent<GameplayManagerComponent>();
        manager->SetQbert(qbert1); // Main player (can be used for win condition)
        if (auto* gameUI = manager->GetGameUI())
        {
            qbert1->AddObserver(gameUI);
            qbert2->AddObserver(gameUI);
        }
    }

    // === Bind inputs ===
    InputBindingHelper::BindPlayer1KeyboardInputs(qbert1.get());
    InputBindingHelper::BindPlayer2GamepadInputs(qbert2.get());
}
