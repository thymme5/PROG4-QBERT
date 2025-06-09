#include "QbertSoundLibrary.h"

std::unordered_map<SoundID, std::string> QbertSoundLibrary::m_SoundMap{};

void QbertSoundLibrary::LoadAllSounds()
{
    Register(SoundID::QbertJump, "../Data/Sounds/QBert Jump.wav");
    Register(SoundID::CoilyEggJump, "../Data/Sounds/Coily Egg Jump.wav");
    Register(SoundID::CoilySnakeJump, "../Data/Sounds/Coily Snake Jump.wav");
    Register(SoundID::RoundComplete, "../Data/Sounds/Round Complete Tune.wav");
    Register(SoundID::ChangeSelection, "../Data/Sounds/Change Selection.wav");
    Register(SoundID::ClearDisks, "../Data/Sounds/Clear Disks.wav");
    Register(SoundID::CoilyFall, "../Data/Sounds/Coily Fall.wav");
    Register(SoundID::DemoSound, "../Data/Sounds/Demo Sound.wav");
    Register(SoundID::DiskLand, "../Data/Sounds/Disk Land.wav");
    Register(SoundID::DiskLift, "../Data/Sounds/Disk Lift.wav");
    Register(SoundID::LevelScreenTune, "../Data/Sounds/Level Screen Tune.wav");
    Register(SoundID::OtherFoesJump, "../Data/Sounds/Other Foes Jump.wav");
    Register(SoundID::QbertFall, "../Data/Sounds/QBert Fall.wav");
    Register(SoundID::QbertHit, "../Data/Sounds/QBert Hit.wav");
    Register(SoundID::SlickSamCaught, "../Data/Sounds/SlickSam Caught.wav");
    Register(SoundID::Swearing, "../Data/Sounds/Swearing.wav");
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
