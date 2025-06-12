#include "CoopMode.h"
#include "QbertSceneBuilder.h"

void CoopMode::Enter()
{
    QbertSceneBuilder::BuildCoopScene(dae::SceneManager::GetInstance().CreateScene(m_SceneName), "../data/levels/Level01Coop.json");
}

void CoopMode::Exit()
{
    dae::SceneManager::GetInstance().RemoveScene(m_SceneName);
}

void CoopMode::Update()
{

}
