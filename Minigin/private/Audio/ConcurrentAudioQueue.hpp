#ifndef MINIGIN_CONCURRENTQUEUE_HPP
#define MINIGIN_CONCURRENTQUEUE_HPP
#include <cstdint>
#include <mutex>
#include <queue>

namespace dae
{
    enum class AudioRequestType
    {
        NONE,
        LOAD,
        PLAY
    };

    struct AudioRequest
    {
        AudioRequestType type;
        uint32_t sound_id;
        float volume;
    };

    class ConcurrentAudioQueue
    {
    public:
        void Push(AudioRequest &&request);
        AudioRequest Pop();

        bool IsEmpty();

    private:
        std::queue<AudioRequest> m_queue;
        std::mutex m_mutex{};
    };
}

#endif //MINIGIN_CONCURRENTQUEUE_HPP
