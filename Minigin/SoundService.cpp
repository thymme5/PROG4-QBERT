#include "SoundService.h"
#include <SDL_mixer.h>
#include <iostream>

namespace dae
{
    SoundService* ServiceLocator::m_pSoundService = nullptr;

    void ServiceLocator::RegisterSoundService(SoundService* service)
    {
        m_pSoundService = service;
    }

    SoundService* ServiceLocator::GetSoundService()
    {
        return m_pSoundService;
    }

    SDLMixerSoundService::SDLMixerSoundService()
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }
        m_WorkerThread = std::thread(&SDLMixerSoundService::ProcessQueue, this);
    }

    SDLMixerSoundService::~SDLMixerSoundService()
    {
        m_Running = false;
        m_CondVar.notify_all();
        if (m_WorkerThread.joinable())
            m_WorkerThread.join();

        for (auto& pair : m_LoadedSounds)
            Mix_FreeChunk(pair.second);

        Mix_CloseAudio();
    }
    void SDLMixerSoundService::SetMuted(bool muted) 
    { 
        std::cout << "muted: " << std::boolalpha << muted << std::endl;

        m_IsMuted = muted;
    }
    bool SDLMixerSoundService::IsMuted() const 
    { 
        return m_IsMuted;
    }
    void SDLMixerSoundService::PlaySound(const std::string& soundFile)
    {
        if (m_IsMuted) return;

        std::lock_guard<std::mutex> lock(m_Mutex);
        m_CommandQueue.push({ SoundCommandType::Play, soundFile });
        m_CondVar.notify_one();
    }

    void SDLMixerSoundService::LoadSound(const std::string& soundFile)
    {
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_CommandQueue.push({ SoundCommandType::Load, soundFile });
        }
        m_CondVar.notify_one();
    }

    void SDLMixerSoundService::StopAllSounds()
    {
        Mix_HaltChannel(-1);
    }

    void SDLMixerSoundService::ProcessQueue()
    {
        while (m_Running)
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            m_CondVar.wait(lock, [this] { return !m_CommandQueue.empty() || !m_Running; });

            while (!m_CommandQueue.empty())
            {
                auto cmd = m_CommandQueue.front();
                m_CommandQueue.pop();
                lock.unlock();

                if (cmd.type == SoundCommandType::Load)
                {
                    if (m_LoadedSounds.find(cmd.soundFile) == m_LoadedSounds.end())
                    {
                        Mix_Chunk* chunk = Mix_LoadWAV(cmd.soundFile.c_str());
                        if (chunk)
                            m_LoadedSounds[cmd.soundFile] = chunk;
                        else
                            std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
                    }
                }
                else if (cmd.type == SoundCommandType::Play)
                {
                    auto it = m_LoadedSounds.find(cmd.soundFile);
                    if (it != m_LoadedSounds.end())
                        Mix_PlayChannel(-1, it->second, 0);
                    else
                        std::cerr << "Sound not loaded: " << cmd.soundFile << std::endl;
                }

                lock.lock();
            }
        }
    }
}