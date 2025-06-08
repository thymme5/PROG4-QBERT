#include "QbertSoundLibrary.h"

std::unordered_map<SoundID, std::string> QbertSoundLibrary::m_SoundMap{};

void QbertSoundLibrary::LoadAllSounds()
{
    Register(SoundID::QbertJump, "../Data/Sounds/QBert Jump.wav");
    Register(SoundID::CoilyEggJump, "../Data/Sounds/Coily Egg Jump.wav");
    Register(SoundID::CoilySnakeJump, "../Data/Sounds/Coily Snake Jump.wav");
    Register(SoundID::RoundComplete, "../Data/Sounds/Round Complete Tune.wav");
    //Register(SoundID::QbertDeath, "../Data/Sounds/QBert Death.wav");
    //Register(SoundID::DiscWarp, "../Data/Sounds/DiscWarp.wav");
}

void QbertSoundLibrary::Play(SoundID id)
{
    auto* service = dae::ServiceLocator::GetSoundService();
    if (!service) return;

    const auto& it = m_SoundMap.find(id);
    if (it != m_SoundMap.end())
    {
        service->PlaySound(it->second);
    }
}

void QbertSoundLibrary::Register(SoundID id, const std::string& path)
{
    auto* service = dae::ServiceLocator::GetSoundService();
    if (!service) return;
    else std::cout << "loading sound " << path << std::endl;
    m_SoundMap[id] = path;
    service->LoadSound(path);
}

bool QbertSoundLibrary::IsPlaying(SoundID id)
{
    auto* service = dae::ServiceLocator::GetSoundService();
    if (!service) return false;

    const auto it = m_SoundMap.find(id);
    if (it != m_SoundMap.end())
    {
        return service->IsPlaying(it->second);
    }

    return false;
}
