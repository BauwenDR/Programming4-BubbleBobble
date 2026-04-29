#include "private/Audio/ConcurrentAudioQueue.hpp"

void dae::ConcurrentAudioQueue::Push(AudioRequest &&request)
{
    std::unique_lock lock(m_mutex);
    m_queue.push(request);
}

dae::AudioRequest dae::ConcurrentAudioQueue::Pop()
{
    std::unique_lock lock(m_mutex);
    auto const val{m_queue.front()};
    m_queue.pop();
    return val;
}

bool dae::ConcurrentAudioQueue::IsEmpty()
{
    std::unique_lock lock(m_mutex);
    return m_queue.empty();
}
