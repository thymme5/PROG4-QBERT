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

	go->AddComponent<dae::TextureComponent>(*go, "logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>(*go, "Programming 4 Assignment", font);
	go->SetPosition(80, 20);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>(*go, "0 FPS", font);
	go->AddComponent<dae::FPScounterComponent>(*go);
	scene.Add(go);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>
		(*go, "Use WASD To move character 1, C to inflict damage, Z and X to pick up pellets \nUse D-Pad to  move character 2, X to inflict damage, A and B to pick up pellets", font);
	go->SetPosition(0, 80);
	scene.Add(go);


	//
	//
	//TODO: FIX THIS BECAUSE ITS AN ABSOLUTE CLUSTERFUCK
	//
	//


	//Character 1
	auto character1 = std::make_shared<dae::GameObject>();
	character1->AddComponent<dae::TextureComponent>(*character1, "character.png");
	character1->AddComponent<dae::MoveComponent>(*character1, 5.0f);
	character1->SetPosition(100, 100);
	scene.Add(character1);

	auto moveUpCommand1 = std::make_shared<dae::MoveCommand>(character1.get(), dae::MovementState::MovingUp, 1.0f);
	inputManager.BindCommand(SDLK_w, KeyState::Down, moveUpCommand1);
	auto stopMoveUpCommand1 = std::make_shared<dae::StopMovingCommand>(character1.get());
	inputManager.BindCommand(SDLK_w, KeyState::Up, stopMoveUpCommand1);

	auto moveDownCommand1 = std::make_shared<dae::MoveCommand>(character1.get(), dae::MovementState::MovingDown, 1.0f);
	inputManager.BindCommand(SDLK_s, KeyState::Down, moveDownCommand1);
	auto stopMoveDownCommand1 = std::make_shared<dae::StopMovingCommand>(character1.get());
	inputManager.BindCommand(SDLK_s, KeyState::Up, stopMoveDownCommand1);

	auto moveLeftCommand1 = std::make_shared<dae::MoveCommand>(character1.get(), dae::MovementState::MovingLeft, 1.0f);
	inputManager.BindCommand(SDLK_a, KeyState::Down, moveLeftCommand1);
	auto stopMoveLeftCommand1 = std::make_shared<dae::StopMovingCommand>(character1.get());
	inputManager.BindCommand(SDLK_a, KeyState::Up, stopMoveLeftCommand1);

	auto moveRightCommand1 = std::make_shared<dae::MoveCommand>(character1.get(), dae::MovementState::MovingRight, 1.0f);
	inputManager.BindCommand(SDLK_d, KeyState::Down, moveRightCommand1);
	auto stopMoveRightCommand1 = std::make_shared<dae::StopMovingCommand>(character1.get());
	inputManager.BindCommand(SDLK_d, KeyState::Up, stopMoveRightCommand1);

	//Character 2
	auto character2 = std::make_shared<dae::GameObject>();
	character2->AddComponent<dae::TextureComponent>(*character2, "character.png");
	character2->AddComponent<dae::MoveComponent>(*character2, 10.0f);
	character2->SetPosition(25, 25);
	scene.Add(character2);

	auto moveUpCommand2 = std::make_shared<dae::MoveCommand>(character2.get(), dae::MovementState::MovingUp, 2.0f);
	inputManager.BindCommand(GamepadButton::DPadUp, KeyState::Down, moveUpCommand2);
	auto stopMoveUpCommand2 = std::make_shared<dae::StopMovingCommand>(character2.get());
	inputManager.BindCommand(GamepadButton::DPadUp, KeyState::Up, stopMoveUpCommand2);

	auto moveDownCommand2 = std::make_shared<dae::MoveCommand>(character2.get(), dae::MovementState::MovingDown, 2.0f);
	inputManager.BindCommand(GamepadButton::DPadDown, KeyState::Down, moveDownCommand2);
	auto stopMoveDownCommand2 = std::make_shared<dae::StopMovingCommand>(character2.get());
	inputManager.BindCommand(GamepadButton::DPadDown, KeyState::Up, stopMoveDownCommand2);

	auto moveLeftCommand2 = std::make_shared<dae::MoveCommand>(character2.get(), dae::MovementState::MovingLeft, 2.0f);
	inputManager.BindCommand(GamepadButton::DPadLeft, KeyState::Down, moveLeftCommand2);
	auto stopMoveLeftCommand2 = std::make_shared<dae::StopMovingCommand>(character2.get());
	inputManager.BindCommand(GamepadButton::DPadLeft, KeyState::Up, stopMoveLeftCommand2);

	auto moveRightCommand2 = std::make_shared<dae::MoveCommand>(character2.get(), dae::MovementState::MovingRight, 2.0f);
	inputManager.BindCommand(GamepadButton::DPadRight, KeyState::Down, moveRightCommand2);
	auto stopMoveRightCommand2 = std::make_shared<dae::StopMovingCommand>(character2.get());
	inputManager.BindCommand(GamepadButton::DPadRight, KeyState::Up, stopMoveRightCommand2);

	//make smaller font
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	//Character 1 observer & UI
	//-------------------------------------------------------------------------------------------------
	//text object 
	go = std::make_shared<dae::GameObject>();
	go->SetPosition(0, 200);

	int startingLives{ 3 }, startingScore{ 0 };
	std::string text = "# lives: " + std::to_string(startingLives) + "\nScore: " + std::to_string(startingScore);
	go->AddComponent<dae::TextComponent>(*go, text, font);
	scene.Add(go);

	auto* character1UI = go->AddComponent<dae::GameUIComponent>(*go, startingLives, startingScore);
	character1->AddObserver(character1UI);

	//character 1 hits character 2
	auto hitCommand = std::make_shared<dae::HitCommand>(character1.get(), character2.get());
	inputManager.BindCommand(SDLK_c, KeyState::Down, hitCommand);

	//10 pellets
	auto pelletCommand = std::make_shared<dae::PelletCommand>(character1.get(), dae::Event::PlayerPickUpPellets10);
	inputManager.BindCommand(SDLK_z, KeyState::Down, pelletCommand);

	//100 pellets
	pelletCommand = std::make_shared<dae::PelletCommand>(character1.get(), dae::Event::PlayerPickUpPellets100);
	inputManager.BindCommand(SDLK_x, KeyState::Down, pelletCommand);
	
	//-------------------------------------------------------------------------------------------------
	// 
	//Character 2 observer & UI
	go = std::make_shared<dae::GameObject>();
	go->SetPosition(0, 300);

	startingLives = 3, startingScore = 0;
	text = "# lives: " + std::to_string(startingLives) + "\nScore: " + std::to_string(startingScore);
	go->AddComponent<dae::TextComponent>(*go, text, font);
	scene.Add(go);

	auto* character2UI = go->AddComponent<dae::GameUIComponent>(*go, startingLives, startingScore);
	character2->AddObserver(character2UI);

	//character 1 hits character 2
	hitCommand = std::make_shared<dae::HitCommand>(character2.get(), character1.get());
	inputManager.BindCommand(GamepadButton::X, KeyState::Down, hitCommand);

	//pellets
	pelletCommand = std::make_shared<dae::PelletCommand>(character2.get(), dae::Event::PlayerPickUpPellets10);
	inputManager.BindCommand(GamepadButton::A, KeyState::Down, pelletCommand);

	pelletCommand = std::make_shared<dae::PelletCommand>(character2.get(), dae::Event::PlayerPickUpPellets100);
	inputManager.BindCommand(GamepadButton::B, KeyState::Down, pelletCommand);

	//-------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	//SOUNDS
	//-------------------------------------------------------------------------------------------------
	auto soundService = dae::ServiceLocator::GetSoundService();
	if (soundService)
	{
		soundService->LoadSound("../Data/sound/damage.wav");
	}
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}