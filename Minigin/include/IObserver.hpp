#ifndef MINIGIN_OBSERVER_HPP
#define MINIGIN_OBSERVER_HPP

#include <cstdint>

namespace dae {
    class IObserver {
    public:
        virtual ~IObserver() = default;

        // The object reference may not be needed in most cases as an observer needs to bind itself to an object.
        // When this is done it often has the object as state
        // We could remove this in the future
        virtual void Notify(GameObject &object, uint32_t event) = 0;
    };
}

#endif //MINIGIN_OBSERVER_HPP