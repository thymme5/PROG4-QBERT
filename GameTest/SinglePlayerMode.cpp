#include "SinglePlayerMode.h"
#include "QbertSceneBuilder.h"
#include "InputManager.h"

SinglePlayerMode::SinglePlayerMode(int levelIndex)
    :
    m_LevelIndex(levelIndex)
{
    
}

void SinglePlayerMode::Enter()
{
    std::cout << "buildcing scene " << std::endl;

    std::stringstream ss;
    ss << "../data/levels/Level0" << m_LevelIndex << "Solo.json";
    std::string levelPath = ss.str();

    QbertSceneBuilder::BuildSinglePlayerScene(dae::SceneManager::GetInstance().CreateScene(m_SceneName), levelPath);
}

void SinglePlayerMode::Exit()
{
    std::cout << "removing scene " << std::endl;
    dae::InputManager::GetInstance().ClearAllBindings();
    dae::SceneManager::GetInstance().RemoveScene(m_SceneName);
}

void SinglePlayerMode::Update()
{

}
