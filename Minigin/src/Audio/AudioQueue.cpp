#include "Audio/AudioQueue.hpp"
#include "private/Audio/AudioQueue.hpp"

#include <condition_variable>
#include <iostream>
#include <thread>
#include <unordered_map>

#include "ServiceLocator.hpp"
#include "private/Audio/ConcurrentAudioQueue.hpp"

namespace
{
    std::jthread m_soundThread{};

    std::condition_variable m_wakeCondition{};
    dae::ConcurrentAudioQueue m_requests{};

    std::unordered_map<uint32_t, std::string> m_sounds{};

    std::mutex m_conditionMutex;
    bool m_shouldExit{};
}

// Public functions
void dae::AudioQueue::LoadSound(uint32_t sound_id, std::string const &fileName)
{
    m_sounds[sound_id] = fileName;
}

void dae::AudioQueue::PlaySound(uint32_t sound_id_hash, float volume)
{
    m_requests.Push({AudioRequestType::PlaySfx, sound_id_hash, volume});
    m_wakeCondition.notify_one();
}

// Private functions
void dae::AudioQueue::Launch()
{
    m_soundThread = std::jthread(&RunSoundThread);
}

void dae::AudioQueue::SendShutdownSignal()
{
    std::unique_lock exitLock{m_conditionMutex};
    m_shouldExit = true;
}

void dae::AudioQueue::Shutdown()
{
    SendShutdownSignal();

    m_wakeCondition.notify_one();
    m_soundThread.join();
}

void dae::AudioQueue::RunSoundThread()
{
    while (!m_shouldExit)
    {
        while (!m_requests.IsEmpty())
        {
            const auto [type, sound_id, volume]{m_requests.Pop()};

            // TODO implement other sound system types
            switch (type)
            {
                case AudioRequestType::PlaySfx:
                    ServiceLocator::GetSoundSystem().PlaySound(sound_id, volume);
                    break;

                default:
                    std::cerr << "Invalid sound operation\n";
                    break;
            }
        }

        std::unique_lock wakeLock{m_conditionMutex};
        m_wakeCondition.wait(wakeLock, [] {return m_shouldExit || !m_requests.IsEmpty();});
    }
}

std::string dae::AudioQueue::GetPathForId(uint32_t sound_id)
{
    if (m_sounds.contains(sound_id))
    {
        return m_sounds[sound_id];
    }

    return "Unknown sound effect";
}
