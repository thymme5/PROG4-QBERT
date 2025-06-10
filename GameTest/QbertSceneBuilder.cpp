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
void QbertSceneBuilder::BuildQbertScene(dae::Scene& scene, const std::string& levelPath, GameModeType mode)
{
    // Get references to input and font resources.
    auto& inputManager = dae::InputManager::GetInstance();
    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

    // (Unused parameters can be discarded or used later if needed.)
    mode;

    // === Gameplay Manager ===
    auto controller = std::make_shared<dae::GameObject>();
    auto* manager = controller->AddComponent<GameplayManagerComponent>(*controller);
    manager->Init(scene, levelPath);
    scene.Add(controller);

    // === Retrieve Tile Map & Starting Tile ===
    auto tileMap = LevelBuilder::GetTileMap();
    // Get the first tile's GameObject and extract its TileComponent.
    auto tileGO = tileMap[0][0];
    auto tileComp = std::shared_ptr<TileComponent>(tileGO->GetComponent<TileComponent>(), [](TileComponent*) {});

    // === FPS Counter ===
    auto go = std::make_shared<dae::GameObject>();
    go->AddComponent<dae::TextComponent>(*go, "0 FPS", font);
    go->AddComponent<dae::FPScounterComponent>(*go);
    scene.Add(go);

    // === Qbert GameObject ===
    auto qbert = std::make_shared<dae::GameObject>();
    qbert->AddComponent<dae::TextureComponent>(*qbert, "Qbert P1 Spritesheet.png", 2.f, 4);
    qbert->AddComponent<QbertMoveComponent>(*qbert);
    auto* qbertMove = qbert->GetComponent<QbertMoveComponent>();
    // Set up Qbert's starting tile and tile map.
    qbertMove->SetCurrentTile(tileComp);
    qbertMove->SetTileMap(LevelBuilder::GetTileComponentMap());
    // Link Qbert to the GameplayManager.
    manager->SetQbert(qbert);

    // === Game UI & Observer Setup ===
    go = std::make_shared<dae::GameObject>();
    auto* gameUI = go->AddComponent<dae::GameUIComponent>(*go);
    go->AddComponent<dae::TextComponent>(*go, " ", dae::ResourceManager::GetInstance().LoadFont("minecraft.ttf", 18));
    go->SetPosition(5, 50);
    // Add UI observer to both Qbert and the gameplay controller.
    qbert->AddObserver(gameUI);
    controller->AddObserver(gameUI);
    scene.Add(go);

    // === Round & Level UI ===
    auto roundGO = std::make_shared<dae::GameObject>();
    roundGO->AddComponent<dae::TextComponent>(*roundGO, "ROUND: 1", font);
    roundGO->SetPosition(400, 80);
    scene.Add(roundGO);

    auto levelGO = std::make_shared<dae::GameObject>();
    levelGO->AddComponent<dae::TextComponent>(*levelGO, "LEVEL: 1", font);
    levelGO->SetPosition(400, 110);
    scene.Add(levelGO);

    // Link the Round and Level texts to the GameUIComponent.
    gameUI->SetRoundText(roundGO->GetComponent<dae::TextComponent>());
    gameUI->SetLevelText(levelGO->GetComponent<dae::TextComponent>());

    // === Add Qbert to the Scene ===
    scene.Add(qbert);

    // === Input Binding for Qbert Movements ===
    using D = Direction;
    // UpLeft
    auto moveUL = std::make_shared<dae::MoveCommand>(qbert.get(), D::UpLeft);
    inputManager.BindCommand(GamepadButton::DPadUp, KeyState::Down, moveUL);
    inputManager.BindCommand(SDLK_UP, KeyState::Down, moveUL);
    // UpRight
    auto moveUR = std::make_shared<dae::MoveCommand>(qbert.get(), D::UpRight);
    inputManager.BindCommand(GamepadButton::DPadRight, KeyState::Down, moveUR);
    inputManager.BindCommand(SDLK_RIGHT, KeyState::Down, moveUR);
    // DownLeft
    auto moveDL = std::make_shared<dae::MoveCommand>(qbert.get(), D::DownLeft);
    inputManager.BindCommand(GamepadButton::DPadLeft, KeyState::Down, moveDL);
    inputManager.BindCommand(SDLK_LEFT, KeyState::Down, moveDL);
    // DownRight
    auto moveDR = std::make_shared<dae::MoveCommand>(qbert.get(), D::DownRight);
    inputManager.BindCommand(GamepadButton::DPadDown, KeyState::Down, moveDR);
    inputManager.BindCommand(SDLK_DOWN, KeyState::Down, moveDR);

    // Finish Round Command binding.
    auto finishCmd = std::make_shared<FinishRoundCommand>(manager);
    inputManager.BindCommand(SDLK_F4, KeyState::Down, finishCmd);

    // === Coily GameObject ===
    auto coily = std::make_shared<dae::GameObject>();
    coily->AddComponent<dae::TextureComponent>(*coily, "testing/coily_egg_test_character.png", 2.0f);
    auto* coilyComponent = coily->AddComponent<CoilyComponent>(*coily);
    coilyComponent->SetTileMap(LevelBuilder::GetTileComponentMap());
    coilyComponent->SetState(std::make_unique<EggState>());
    coilyComponent->SetCurrentTile(tileComp);
    coilyComponent->SetQbert(qbert);
    scene.Add(coily);
    manager->SetCoily(coily);

    // === Sound Setup ===
    auto toggleMute = std::make_shared<ToggleMuteCommand>();
    inputManager.BindCommand(SDLK_F2, KeyState::Down, toggleMute);

    auto soundService = dae::ServiceLocator::GetSoundService();
    if (soundService)
    {
        soundService->SetVolume(10);
        QbertSoundLibrary::LoadAllSounds();
    }
}