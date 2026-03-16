#ifndef MINIGIN_EVENTMANAGER_HPP
#define MINIGIN_EVENTMANAGER_HPP

#include <cstdint>
#include <unordered_map>
#include <vector>

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
        void DetachHandler(IEventHandler *handler);

        void TriggerEvents();
    private:
        friend class Singleton;
        EventManager() = default;

        std::unordered_map<uint32_t, IEventHandler*> m_handlers;

        std::vector<uint32_t> m_messages{};
        std::vector<uint32_t> m_newMessages{};

        bool m_processingEvents{};
    };
}

#endif //MINIGIN_EVENTMANAGER_HPP