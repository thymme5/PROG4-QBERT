#include "CoopMode.h"
#include "QbertSceneBuilder.h"

CoopMode::CoopMode(int levelIndex) :
    m_LevelIndex(levelIndex)
{

}
void CoopMode::Enter()
{
    std::stringstream ss;
    ss << "../data/levels/Level0" << m_LevelIndex << "Coop.json";
    std::string levelPath = ss.str();

    QbertSceneBuilder::BuildCoopScene(dae::SceneManager::GetInstance().CreateScene(m_SceneName), levelPath);
}

void CoopMode::Exit()
{
    dae::SceneManager::GetInstance().RemoveScene(m_SceneName);
}

void CoopMode::Update()
{

}
