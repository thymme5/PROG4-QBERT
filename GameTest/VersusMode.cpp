#include "VersusMode.h"
#include "QbertSceneBuilder.h"


VersusMode::VersusMode(int levelIndex) :
    m_LevelIndex(levelIndex)
{

}

void VersusMode::Enter()
{
    std::stringstream ss;
    ss << "../data/levels/Level0" << m_LevelIndex << "Versus.json";
    std::string levelPath = ss.str();

    QbertSceneBuilder::BuildVersusScene(dae::SceneManager::GetInstance().CreateScene(m_SceneName),levelPath);
}

void VersusMode::Exit()
{
    dae::SceneManager::GetInstance().RemoveScene(m_SceneName);
}

void VersusMode::Update()
{

}
