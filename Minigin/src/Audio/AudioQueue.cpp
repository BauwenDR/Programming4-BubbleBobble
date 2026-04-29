#include "Audio/AudioQueue.hpp"
#include "private/Audio/AudioQueue.hpp"

#include <condition_variable>
#include <iostream>
#include <thread>

#include "ServiceLocator.hpp"
#include "private/Audio/ConcurrentAudioQueue.hpp"

namespace
{
    std::jthread m_soundThread;

    std::condition_variable m_wakeCondition{};
    dae::ConcurrentAudioQueue m_requests{};
    std::mutex m_conditionMutex;
    bool m_shouldExit{};
}

// Public functions
void dae::AudioQueue::PlaySound(uint32_t sound_id_hash, float volume)
{
    m_requests.Push({AudioRequestType::PLAY, sound_id_hash, volume});
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

            switch (type)
            {
                case AudioRequestType::PLAY:
                    ServiceLocator::GetSoundSystem().PlaySound(sound_id, volume);
                    break;

                case AudioRequestType::LOAD:
                    ServiceLocator::GetSoundSystem().PreLoadSound(sound_id);
                    break;

                default:
                case AudioRequestType::NONE:
                    std::cerr << "Invalid sound operation\n";
                    break;
            }
        }

        std::unique_lock wakeLock{m_conditionMutex};
        m_wakeCondition.wait(wakeLock, [] {return m_shouldExit || !m_requests.IsEmpty();});
    }
}
