#include "CoopMode.h"
#include "QbertSceneBuilder.h"

void CoopMode::Enter()
{
    QbertSceneBuilder::BuildCoopScene(dae::SceneManager::GetInstance().CreateScene("CoopModeScene"), "../data/levels/Level01Coop.json");
}

void CoopMode::Exit()
{
}

void CoopMode::Update()
{

}
