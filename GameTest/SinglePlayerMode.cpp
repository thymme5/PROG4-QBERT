#include "SinglePlayerMode.h"
#include "QbertSceneBuilder.h"

void SinglePlayerMode::Enter()
{
    QbertSceneBuilder::BuildQbertScene(dae::SceneManager::GetInstance().CreateScene("SinglePlayerModeScene"), "../data/levels/Level01Solo.json");
}

void SinglePlayerMode::Exit()
{
    dae::SceneManager::GetInstance().RemoveScene("SinglePlayerModeScene");
}

void SinglePlayerMode::Update()
{

}
