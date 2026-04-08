#include "Event/EventManager.hpp"

#include <algorithm>

void dae::EventManager::SendEvent(uint32_t event) {
    m_ringBuffer.Push(event);
}

void dae::EventManager::AttachHandler(uint32_t event, IEventHandler *handler) {
    m_handlers.emplace(event, handler);
}

void dae::EventManager::DetachHandler(const IEventHandler *handler) {
    std::erase_if(m_handlers, [handler] (const auto &eventHandler) {return eventHandler.second == handler; });
}

void dae::EventManager::TriggerEvents() {
    while (!m_ringBuffer.IsEmpty())
    {
        const uint32_t event{m_ringBuffer.Pop()};

        if (!m_handlers.contains(event)) continue;

        const auto [firstHandler, lastHandler]{m_handlers.equal_range(event)};
        for (const auto&[eventName, handler] : std::ranges::subrange(firstHandler, lastHandler))
        {
            handler->HandleEvent(event);
        }
    }
}
