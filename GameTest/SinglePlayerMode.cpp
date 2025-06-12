#include "SinglePlayerMode.h"
#include "QbertSceneBuilder.h"
#include "InputManager.h"

void SinglePlayerMode::Enter()
{
    QbertSceneBuilder::BuildSinglePlayerScene(dae::SceneManager::GetInstance().CreateScene(m_SceneName), "../data/levels/Level01Solo.json");
}

void SinglePlayerMode::Exit()
{
    dae::InputManager::GetInstance().ClearAllBindings();
    dae::SceneManager::GetInstance().RemoveScene(m_SceneName);
}

void SinglePlayerMode::Update()
{

}
