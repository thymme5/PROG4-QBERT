#include "VersusMode.h"
#include "QbertSceneBuilder.h"

void VersusMode::Enter()
{
    QbertSceneBuilder::BuildVersusScene(dae::SceneManager::GetInstance().CreateScene(m_SceneName), "../data/levels/Level01Versus.json");
}

void VersusMode::Exit()
{
    dae::SceneManager::GetInstance().RemoveScene(m_SceneName);
}

void VersusMode::Update()
{

}
