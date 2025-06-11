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
#include "MainMenuUIComponent.h"
#include "GameModeManager.h"
#include "MainMenu.h"

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
	//build main menu
	GameModeManager::GetInstance().SetMode(std::make_unique<MainMenu>());
}
int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}