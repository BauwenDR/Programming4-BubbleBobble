#ifndef MINIGIN_EVENTRINGBUFFER_HPP
#define MINIGIN_EVENTRINGBUFFER_HPP
#include <array>
#include <cstdint>

// Ring buffer specifically made to handle uint32_t (sbdm hashes)
namespace dae
{
    class EventRingBuffer final
    {
    public:
        void Push(uint32_t value);
        [[nodiscard]] uint32_t Pop();

        [[nodiscard]] bool IsFull() const;
        [[nodiscard]] bool IsEmpty() const;

    private:
        // 64 was not chosen for any specific reasons.
        // When writing this it seemed big enough to never have an overflow
        // But also not too big to waste memory
        // Anyway, to finetune this number benchmarking is required
        constexpr static int BUFFER_SIZE{64};

        std::array<uint32_t, BUFFER_SIZE> m_ringBuffer{};

        int m_bufferHead{};
        int m_bufferTail{};

        bool m_isFull{false};

        static inline int IncrementValue(int value);
    };
}

#endif //MINIGIN_EVENTRINGBUFFER_HPP