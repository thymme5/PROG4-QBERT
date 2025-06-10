#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <iostream>

//engine files
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "SoundService.h"

//Components
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPScounterComponent.h"
#include "ImGuiComponent.h"
#include "GameUIComponent.h"
#include "CoilyComponent.h"
#include "EggState.h"
#include "TileComponent.h"
#include "GameplayManagerComponent.h"

//Commands
#include "MoveCommand.h"
#include "ToggleMuteCommand.h"
#include "FinishRoundCommand.h"

//other misc
#include "LevelBuilder.h"
#include "QbertSceneBuilder.h"
#include "GameModeManager.h"

//sound related 
#include "QbertSoundLibrary.h"



void load()
{
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//auto go = std::make_shared<dae::GameObject>();
	//auto& inputManager = dae::InputManager::GetInstance();

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//// === GameplayManager ===
	////level loading also gets handled here
	//auto controller = std::make_shared<dae::GameObject>();
	//controller->AddComponent<GameplayManagerComponent>(*controller);
	//auto* manager = controller->AddComponent<GameplayManagerComponent>(*controller);
	//scene.Add(controller);
	//
	//auto tileMap = LevelBuilder::GetTileMap();
	//auto tileGO = tileMap[0][0];
	//auto tileComp = std::shared_ptr<TileComponent>(tileGO->GetComponent<TileComponent>(), [](TileComponent*) {});

	//// === FPS counter ===
	//go = std::make_shared<dae::GameObject>();
	//go->AddComponent<dae::TextComponent>(*go, "0 FPS", font);
	//go->AddComponent<dae::FPScounterComponent>(*go);
	//scene.Add(go);

	//// === Qbert GameObject ===
	//auto qbert = std::make_shared<dae::GameObject>();
	//qbert->AddComponent<dae::TextureComponent>(*qbert, "Qbert P1 Spritesheet.png", 2.f, 4);
	//qbert->AddComponent<QbertMoveComponent>(*qbert);
	//auto qbertMove = qbert->GetComponent<QbertMoveComponent>();

	//qbertMove->SetCurrentTile(tileComp);
	//qbertMove->SetTileMap(LevelBuilder::GetTileComponentMap());
	//manager->SetQbert(qbert);

	//// === make a GameUIComponent and put a tracker on qberts ass === 
	//go = std::make_shared<dae::GameObject>();
	//auto* gameUI = go->AddComponent<dae::GameUIComponent>(*go);
	//go->AddComponent<dae::TextComponent>(*go, " ", dae::ResourceManager::GetInstance().LoadFont("minecraft.ttf", 18));
	//go->SetPosition(5, 50);

	////add UI as observer to objects
	//qbert->AddObserver(gameUI);
	//controller->AddObserver(gameUI);

	//scene.Add(go);

	//// === Round UI ===
	//auto roundGO = std::make_shared<dae::GameObject>();
	//roundGO->AddComponent<dae::TextComponent>(*roundGO, "ROUND: 1", font);
	//roundGO->SetPosition(400, 80);
	//scene.Add(roundGO);

	//// === Level UI ===
	//auto levelGO = std::make_shared<dae::GameObject>();
	//levelGO->AddComponent<dae::TextComponent>(*levelGO, "LEVEL: 1", font);
	//levelGO->SetPosition(400, 110);
	//scene.Add(levelGO);

	//// Link to GameUIComponent
	//gameUI->SetRoundText(roundGO->GetComponent<dae::TextComponent>());
	//gameUI->SetLevelText(levelGO->GetComponent<dae::TextComponent>());

	//// === add qberts ass to the scene cuz he's important after all === 
	//scene.Add(qbert);

	//// === Input Binding for Qbert ===
	//using D = Direction;

	////UP = UpLeft
	//auto moveUL = std::make_shared<dae::MoveCommand>(qbert.get(), D::UpLeft);
	//inputManager.BindCommand(GamepadButton::DPadUp, KeyState::Down, moveUL);
	//inputManager.BindCommand(SDLK_UP, KeyState::Down, moveUL);

	////RIGHT = UpRight
	//auto moveUR = std::make_shared<dae::MoveCommand>(qbert.get(), D::UpRight);
	//inputManager.BindCommand(GamepadButton::DPadRight, KeyState::Down, moveUR);
	//inputManager.BindCommand(SDLK_RIGHT, KeyState::Down, moveUR);

	////LEFT = DownLeft
	//auto moveDL = std::make_shared<dae::MoveCommand>(qbert.get(), D::DownLeft);
	//inputManager.BindCommand(GamepadButton::DPadLeft, KeyState::Down, moveDL);
	//inputManager.BindCommand(SDLK_LEFT, KeyState::Down, moveDL);

	////DOWN = DownRight
	//auto moveDR = std::make_shared<dae::MoveCommand>(qbert.get(), D::DownRight);
	//inputManager.BindCommand(GamepadButton::DPadDown, KeyState::Down, moveDR);
	//inputManager.BindCommand(SDLK_DOWN, KeyState::Down, moveDR);

	////F4 = FINISH ROUND COMMAND
	//auto finishCmd = std::make_shared<FinishRoundCommand>(manager);
	//inputManager.BindCommand(SDLK_F4, KeyState::Down, finishCmd);

	//// === Coily GameObject ===
	//auto coily = std::make_shared<dae::GameObject>();
	//coily->AddComponent<dae::TextureComponent>(*coily, "testing/coily_egg_test_character.png", 2.0f);

	//auto* coilyComponent = coily->AddComponent<CoilyComponent>(*coily);
	//coilyComponent->SetTileMap(LevelBuilder::GetTileComponentMap());
	//coilyComponent->SetState(std::make_unique<EggState>()); 
	//coilyComponent->SetCurrentTile(tileComp); 
	//coilyComponent->SetQbert(qbert);

	//scene.Add(coily);
	//manager->SetCoily(coily);

	////-------------------------------------------------------------------------------------------------
	////-------------------------------------------------------------------------------------------------
	////SOUNDS
	////-------------------------------------------------------------------------------------------------
	////-------------------------------------------------------------------------------------------------
	//auto toggleMute = std::make_shared<ToggleMuteCommand>();
	//inputManager.BindCommand(SDLK_F2, KeyState::Down, toggleMute);

	//auto soundService = dae::ServiceLocator::GetSoundService(); 
	//if (soundService)
	//{
	//	soundService->SetVolume(10);
	//	QbertSoundLibrary::LoadAllSounds();
	//}
	
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	// Create the scene manually
	auto& scene = dae::SceneManager::GetInstance().CreateScene("QbertGame");

	// Build the actual scene
	QbertSceneBuilder::BuildQbertScene(scene, "../data/levels/Level01Solo.json", GameModeType::SinglePlayer);


}
int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}