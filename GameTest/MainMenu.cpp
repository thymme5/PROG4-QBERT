#include "MainMenu.h"
#include "QbertSceneBuilder.h"
#include "InputManager.h"

void MainMenu::Enter() 
{
	QbertSceneBuilder::BuildMainMenu(dae::SceneManager::GetInstance().CreateScene("MainMenu"), 
		dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
}
void MainMenu::Exit() 
{
	dae::InputManager::GetInstance().ClearAllBindings();
	dae::SceneManager::GetInstance().RemoveScene("MainMenu");
}
void MainMenu::Update() 
{

}