#ifndef MINIGIN_CONCURRENTQUEUE_HPP
#define MINIGIN_CONCURRENTQUEUE_HPP
#include <cstdint>
#include <mutex>
#include <queue>

namespace dae
{
    enum class AudioRequestType
    {
        None,
        PreLoad,       // TODO unimplemented
        PlaySfx,
        PlayStream     // TODO unimplemented
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
