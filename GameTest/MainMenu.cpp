#include "MainMenu.h"
#include "QbertSceneBuilder.h"

void MainMenu::Enter() 
{
	QbertSceneBuilder::BuildMainMenu(dae::SceneManager::GetInstance().CreateScene("MainMenu"), 
		dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
}
void MainMenu::Exit() 
{
	dae::SceneManager::GetInstance().RemoveScene("MainMenu");
}
void MainMenu::Update() 
{

}