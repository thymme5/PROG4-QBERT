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

//Commands
#include "MoveCommand.h"

//other misc
#include "LevelBuilder.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto go = std::make_shared<dae::GameObject>();
	auto& inputManager = dae::InputManager::GetInstance();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	// === Level Loading ===
	LevelBuilder::LoadLevel1(scene);
	auto tileMap = LevelBuilder::GetTileMap();
	auto tileGO = tileMap[0][0];
	auto tileComp = std::shared_ptr<TileComponent>(tileGO->GetComponent<TileComponent>(), [](TileComponent*) {});

	// === FPS counter ===
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>(*go, "0 FPS", font);
	go->AddComponent<dae::FPScounterComponent>(*go);
	scene.Add(go);

	// === Qbert GameObject ===
	auto qbert = std::make_shared<dae::GameObject>();
	qbert->AddComponent<dae::TextureComponent>(*qbert, "Qbert P1 Spritesheet.png", 2.f, 4);
	qbert->AddComponent<QbertMoveComponent>(*qbert);
	auto qbertMove = qbert->GetComponent<QbertMoveComponent>();

	qbertMove->SetCurrentTile(tileComp);
	qbertMove->SetTileMap(LevelBuilder::GetTileComponentMap());

	// === make a GameUIComponent and put a tracker on qberts ass === 
	go = std::make_shared<dae::GameObject>();
	auto* gameUI = go->AddComponent<dae::GameUIComponent>(*go);
	go->AddComponent<dae::TextComponent>(*go, " ", dae::ResourceManager::GetInstance().LoadFont("minecraft.ttf", 18));
	go->SetPosition(5, 50);
	qbert->AddObserver(gameUI);

	scene.Add(go);

	// === add qberts ass to the scene cuz he's important after all === 
	scene.Add(qbert);

	// === Input Binding for Qbert ===
	using D = Direction;

	//UP = UpLeft
	auto moveUL = std::make_shared<dae::MoveCommand>(qbert.get(), D::UpLeft);
	inputManager.BindCommand(GamepadButton::DPadUp, KeyState::Down, moveUL);
	inputManager.BindCommand(SDLK_UP, KeyState::Down, moveUL);

	//RIGHT = UpRight
	auto moveUR = std::make_shared<dae::MoveCommand>(qbert.get(), D::UpRight);
	inputManager.BindCommand(GamepadButton::DPadRight, KeyState::Down, moveUR);
	inputManager.BindCommand(SDLK_RIGHT, KeyState::Down, moveUR);

	//LEFT = DownLeft
	auto moveDL = std::make_shared<dae::MoveCommand>(qbert.get(), D::DownLeft);
	inputManager.BindCommand(GamepadButton::DPadLeft, KeyState::Down, moveDL);
	inputManager.BindCommand(SDLK_LEFT, KeyState::Down, moveDL);

	//DOWN = DownRight
	auto moveDR = std::make_shared<dae::MoveCommand>(qbert.get(), D::DownRight);
	inputManager.BindCommand(GamepadButton::DPadDown, KeyState::Down, moveDR);
	inputManager.BindCommand(SDLK_DOWN, KeyState::Down, moveDR);

	// === Coily GameObject ===
	auto coily = std::make_shared<dae::GameObject>();
	coily->AddComponent<dae::TextureComponent>(*coily, "testing/coily_egg_test_character.png", 2.0f);
	// coily->AddComponent<dae::MoveComponent>(*coily, 10.0f); //replace this shit for coilymovementcomponent

	auto* coilyComponent = coily->AddComponent<CoilyComponent>(*coily);
	coilyComponent->SetTileMap(LevelBuilder::GetTileComponentMap());
	coilyComponent->SetState(std::make_unique<EggState>()); 
	coilyComponent->SetCurrentTile(tileComp); 
	coilyComponent->SetQbert(qbert);

	//coily->SetPosition(256.f, 0.f); 
	scene.Add(coily);

	//-------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	//SOUNDS
	//-------------------------------------------------------------------------------------------------
	auto soundService = dae::ServiceLocator::GetSoundService(); 
	if (soundService)
	{
		std::filesystem::path path = "../Data/Sounds/QBert Jump.wav";
		std::cout << "Trying to load: " << std::filesystem::absolute(path) << "\n";
		soundService->LoadSound("../Data/Sounds/QBert Jump.wav");
	}
}
int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}