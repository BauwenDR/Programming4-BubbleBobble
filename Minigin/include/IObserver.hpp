#ifndef MINIGIN_OBSERVER_HPP
#define MINIGIN_OBSERVER_HPP

namespace dae {
    class IObserver {
    public:
        virtual ~IObserver() = default;
        virtual void Notify(GameObject &object, uint32_t event) = 0;
    };
}

#endif //MINIGIN_OBSERVER_HPP