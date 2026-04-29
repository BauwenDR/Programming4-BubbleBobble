#include "PlayerSoundProducer.hpp"

#include "GameObject.hpp"
#include "Audio/AudioQueue.hpp"
#include "Event/Sdbm.hpp"

void PlayerSoundProducer::Start()
{
    GetGameObject().AddObserver(this);
}

void PlayerSoundProducer::Notify(uint32_t event, const dae::ObserverData*)
{
    switch (event)
    {
        case dae::sdbm_hash("on_jump"):
            dae::AudioQueue::PlaySound(dae::sdbm_hash("PlayerJump"), 1.0f);
            break;
        case dae::sdbm_hash("on_pickup"):
            dae::AudioQueue::PlaySound(dae::sdbm_hash("Pickup"), 1.0f);
            break;

        default:
            break;
    }
}
