#pragma once

#include <string>
#include <unordered_map>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

struct Mix_Chunk; // Forward declaration

namespace dae // follow your project’s namespace if Minigin uses 'dae'
{
    class SoundService
    {
    public:
        virtual ~SoundService() = default;
        virtual void PlaySound(const std::string& soundFile) = 0;
        virtual void LoadSound(const std::string& soundFile) = 0;
        virtual void StopAllSounds() = 0;
    };

    class SDLMixerSoundService final : public SoundService
    {
    public:
        SDLMixerSoundService();
        ~SDLMixerSoundService() override;

        void PlaySound(const std::string& soundFile) override;
        void LoadSound(const std::string& soundFile) override;
        void StopAllSounds() override;

    private:
        void ProcessQueue();

        enum class SoundCommandType { Play, Load };

        struct SoundCommand
        {
            SoundCommandType type;
            std::string soundFile;
        };

        std::queue<SoundCommand> m_CommandQueue;
        std::mutex m_Mutex;
        std::condition_variable m_CondVar;
        std::atomic<bool> m_Running{ true };
        std::thread m_WorkerThread;

        std::unordered_map<std::string, Mix_Chunk*> m_LoadedSounds;
    };

    class ServiceLocator
    {
    public:
        static SoundService* GetSoundService();
        static void RegisterSoundService(SoundService* service);

    private:
        static SoundService* m_pSoundService;
    };
}
