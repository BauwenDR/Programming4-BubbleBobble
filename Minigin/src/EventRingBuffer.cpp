#include "EventRingBuffer.hpp"

#include <iostream>
#include <stdexcept>

void EventRingBuffer::Push(uint32_t value)
{
    m_ringBuffer[m_bufferHead] = value;

    if (IsFull()) {
        m_bufferTail = IncrementValue(m_bufferTail);

        std::cout << "Event Ring Buffer overflowed, overwriting values" << std::endl;
    }

    m_bufferHead = IncrementValue(m_bufferHead);
    m_isFull = m_bufferHead == m_bufferTail;
}

uint32_t EventRingBuffer::Pop()
{
    if (IsEmpty())
    {
        throw std::out_of_range("Attempted to remove from an empty ring buffer");
    }

    const uint32_t value = m_ringBuffer[m_bufferTail];
    m_isFull = false;
    m_bufferTail = IncrementValue(m_bufferTail);

    return value;
}

bool EventRingBuffer::IsFull() const
{
    return m_isFull;
}

bool EventRingBuffer::IsEmpty() const
{
    return !m_isFull && m_bufferHead == m_bufferTail;
}

int EventRingBuffer::IncrementValue(int value)
{
    return (value + 1) % BUFFER_SIZE;
}
