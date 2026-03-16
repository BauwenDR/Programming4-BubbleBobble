#include "EventManager.hpp"

void dae::EventManager::SendEvent(uint32_t event) {
    if (m_processingEvents)
    {
        m_newMessages.emplace_back(event);
    }
    else
    {
        m_messages.emplace_back(event);
    }
}

void dae::EventManager::AttachHandler(uint32_t event, IEventHandler *handler) {
    m_handlers.emplace(event, handler);
}

void dae::EventManager::DetachHandler(IEventHandler *handler) {
    std::erase_if(m_handlers, [handler] (const auto &eventHandler) {return eventHandler.second == handler; });
}

void dae::EventManager::TriggerEvents() {
    m_processingEvents = true;
    for (const auto &event : m_messages) {
        if (!m_handlers.contains(event)) continue;

        m_handlers[event]->HandleEvent(event);
    }
    m_processingEvents = false;

    m_messages.clear();

    // If there were any new messages while processing messages push them to the queue for the next frame
    if (m_newMessages.empty()) return;

    m_messages.emplace(m_newMessages.begin(), m_newMessages.size());
    m_newMessages.clear();

}
