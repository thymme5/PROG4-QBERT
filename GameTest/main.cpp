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

#include <iostream>


//for testing purposes
#include <windows.h>


//Components
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPScounterComponent.h"
#include "ImGuiComponent.h"
#include "GameUIComponent.h"
#include "MoveComponent.h"
#include "CoilyComponent.h"
#include "EggState.h"

//Commands
#include "StopMovingCommand.h"
#include "TestCommand.h"
#include "MoveCommand.h"
#include "HitCommand.h"
#include "PelletCommand.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto go = std::make_shared<dae::GameObject>();
	auto& inputManager = dae::InputManager::GetInstance();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>(*go, "0 FPS", font);
	go->AddComponent<dae::FPScounterComponent>(*go);
	scene.Add(go);

	// === Q*bert GameObject ===
	auto qbert = std::make_shared<dae::GameObject>();
	qbert->AddComponent<dae::TextureComponent>(*qbert, "testing/qbert_test_character.png", 2.f);
	qbert->AddComponent<dae::MoveComponent>(*qbert, 10.0f);
	qbert->SetPosition(25, 25);
	scene.Add(qbert);

	// === Input Binding for Q*bert ===
	auto qbertMoveUp = std::make_shared<dae::MoveCommand>(qbert.get(), dae::MovementState::MovingUp, 2.0f);
	inputManager.BindCommand(GamepadButton::DPadUp, KeyState::Down, qbertMoveUp);
	auto qbertStopUp = std::make_shared<dae::StopMovingCommand>(qbert.get());
	inputManager.BindCommand(GamepadButton::DPadUp, KeyState::Up, qbertStopUp);

	auto qbertMoveDown = std::make_shared<dae::MoveCommand>(qbert.get(), dae::MovementState::MovingDown, 2.0f);
	inputManager.BindCommand(GamepadButton::DPadDown, KeyState::Down, qbertMoveDown);
	auto qbertStopDown = std::make_shared<dae::StopMovingCommand>(qbert.get());
	inputManager.BindCommand(GamepadButton::DPadDown, KeyState::Up, qbertStopDown);

	auto qbertMoveLeft = std::make_shared<dae::MoveCommand>(qbert.get(), dae::MovementState::MovingLeft, 2.0f);
	inputManager.BindCommand(GamepadButton::DPadLeft, KeyState::Down, qbertMoveLeft);
	auto qbertStopLeft = std::make_shared<dae::StopMovingCommand>(qbert.get());
	inputManager.BindCommand(GamepadButton::DPadLeft, KeyState::Up, qbertStopLeft);

	auto qbertMoveRight = std::make_shared<dae::MoveCommand>(qbert.get(), dae::MovementState::MovingRight, 2.0f);
	inputManager.BindCommand(GamepadButton::DPadRight, KeyState::Down, qbertMoveRight);
	auto qbertStopRight = std::make_shared<dae::StopMovingCommand>(qbert.get());
	inputManager.BindCommand(GamepadButton::DPadRight, KeyState::Up, qbertStopRight);

	// === Coily GameObject ===
	auto coily = std::make_shared<dae::GameObject>();
	coily->AddComponent<dae::TextureComponent>(*coily, "testing/coily_egg_test_character.png", 2.0f);

	
	// coily->AddComponent<dae::MoveComponent>(*coily, 10.0f); // Only if needed

	auto* coilyComponent = coily->AddComponent<CoilyComponent>(*coily);
	coilyComponent->SetState(std::make_unique<EggState>()); 

	coily->SetPosition(256.f, 0.f); 
	scene.Add(coily);


	//-------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	//SOUNDS
	//-------------------------------------------------------------------------------------------------
	auto soundService = dae::ServiceLocator::GetSoundService();
	if (soundService)
	{
		soundService->LoadSound("sounds/Change Selection.wav");
	}
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}