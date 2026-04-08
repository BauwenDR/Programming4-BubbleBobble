#ifndef MINIGIN_EVENTMANAGER_HPP
#define MINIGIN_EVENTMANAGER_HPP

#include <cstdint>
#include <unordered_map>

#include "EventRingBuffer.hpp"
#include "Singleton.hpp"

namespace dae {
    class IEventHandler {
    public:
        virtual ~IEventHandler() = default;
        virtual void HandleEvent(uint32_t event) = 0;
    };

    class EventManager final : public Singleton<EventManager> {
    public:
        void SendEvent(uint32_t event);
        void AttachHandler(uint32_t event, IEventHandler *handler);
        void DetachHandler(const IEventHandler *handler);

        void TriggerEvents();
    private:
        friend class Singleton;
        EventManager() = default;

        std::unordered_multimap<uint32_t, IEventHandler*> m_handlers{};

        EventRingBuffer m_ringBuffer{};
    };
}

#endif //MINIGIN_EVENTMANAGER_HPP